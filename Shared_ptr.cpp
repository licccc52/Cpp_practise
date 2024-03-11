#include<mutex>

template<typename T>
class Shared_ptr {
private:
    // 成员变量
    T *ptr_{nullptr};
    int *ref_count_{nullptr};
    std::mutex *mutex_{nullptr};
public:
    /******************** 构造函数和析构函数 ********************/
    // 默认构造函数
    constexpr Shared_ptr() noexcept = default;

    // 普通构造函数
    explicit Shared_ptr(T *ptr) : ptr_{ptr} {
        if (this->ptr_ != nullptr) {
            this->ref_count_ = new int{1};
            this->mutex_ = new std::mutex{};
        }
    }

    // 从四行代码看右值引用：https://www.cnblogs.com/qicosmos/p/4283455.html
    // - move 本意为 "移动"，但该函数并不能移动任何数据，它的功能很简单，就是将某个左值强制转化为右值。
    // - forward 完美转发，根据右值判断的推倒，调用forward 传出的值，若原来是一个右值，那么他转出来就是一个右值，否则为一个左值。这样的处理就完美的转发了原有参数的左右值属性，不会造成一些不必要的拷贝

    // 拷贝构造函数
    Shared_ptr(const Shared_ptr &rhs) noexcept: ptr_{rhs.ptr_}, ref_count_{rhs.ref_count_}, mutex_{rhs.mutex_} {
        if (this->ptr_ != nullptr) {
            this->addRefCount();
        }
    }

    // 移动构造函数
    Shared_ptr(Shared_ptr &&rhs) noexcept: ptr_{rhs.ptr_}, ref_count_{rhs.ref_count_}, mutex_{rhs.mutex_} {
        // right hand side is nullptr
        rhs.ptr_ = nullptr;
        rhs.ref_count_ = nullptr;
        rhs.mutex_ = nullptr;
    }

    // 析构函数
    ~Shared_ptr() noexcept {
        this->decrRefCount();
    }

    /******************** 运算符重载 ********************/
    // 拷贝赋值运算符
    Shared_ptr &operator=(const Shared_ptr &rhs) {
        Shared_ptr{rhs}.swap(*this);
        return *this;
    }

    // 移动赋值运算符
    Shared_ptr &operator=(Shared_ptr &&rhs) noexcept {
        Shared_ptr{std::move(rhs)}.swap(*this);
        return *this;
    }

    // 取值
    T &operator*() const noexcept {
        return *this->ptr_;
    }

    // 取指针
    T &operator->() const noexcept {
        return this->ptr_;
    }

    // 到 bool 的隐式转换
    explicit operator bool() const noexcept {
        return static_cast<bool>(ptr_);
    }

    /******************** 成员函数 ********************/
    // 获取指针
    T *get() const noexcept {
        return ptr_;
    }

    // 获取引用计数
    int use_count() const noexcept {
        return this->ref_count_ == nullptr ? 0 : *this->ref_count_;
    }

    // 引用计数是否唯一
    bool unique() const noexcept {
        return *this->ref_count_ == 1;
    }

    // 重置指针
    void reset() noexcept {
        Shared_ptr{}.swap(*this);
    }

    // 重置指针
    void reset(T *ptr) {
        Shared_ptr{ptr}.swap(*this);
    }

    // swap函数
    void swap(Shared_ptr &rhs) noexcept {
        std::swap(this->ptr_, rhs.ptr_);
        std::swap(this->ref_count_, rhs.ref_count_);
        std::swap(this->mutex_, rhs.mutex_);
    }

private:
    // 增加引用计数
    void addRefCount() {
        mutex_->lock();
        ++(*ref_count_);
        mutex_->unlock();
    }

    // 减少引用计数，如果为零，则释放指针
    void decrRefCount() {
        bool deleteflag = false;
        mutex_->lock();
        if (--(*ref_count_) == 0) {
            delete ptr_;
            delete ref_count_;
            deleteflag = true;
        }
        mutex_->unlock();
        if (deleteflag) {
            delete mutex_;
        }
    }
};

// 函数模板
template<typename T>
auto make_Shared(T v) {
    return Shared_ptr<T>{new T(v)};
}
