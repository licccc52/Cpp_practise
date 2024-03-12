#include <iostream>
// C++ 中 
//右值 : 取不到地址的表达式
//左值 : 可以取到地址的表达式
// 常量对象为代表的左值不能作为赋值语句的左侧运算对象
// 某些表达式的求职结果是对象, 但他们是右值
template<typename T>
class SmartPointer {
private:
    T* ptr;

public:
    explicit SmartPointer(T* p = nullptr) : ptr(p) {}
    //禁止隐式类型转患
    //如果没有 explicit 关键字，可以像这样隐式地创建一个 SmartPointer 对象：SmartPointer<int> ptr = new int(42);
    //但是由于有了 explicit 关键字，必须显式地创建对象：SmartPointer<int> ptr(new int(42));。
    ~SmartPointer() {
        delete ptr;
    }

    // 拷贝构造函数
    //拷贝构造函数 是一种特殊的构造函数，它在创建对象时，是使用同一类中之前创建的对象来初始化新创建的对象

    //const SmartPointer<T>& other：这是拷贝构造函数的参数，它是一个常量引用，用于接收另一个智能指针对象的引用。
    //通过使用常量引用，可以确保在拷贝过程中不会修改原始对象。
    SmartPointer(const SmartPointer<T>& other) { //SmartPointer<T>：这是一个模板类的定义，可以指向类型为 T 的对象。
    
        ptr = new T;
        *ptr = *(other.ptr);
    }

    // 移动构造函数
    //noexcept： 异常说明符, 用于指示该函数不会抛出异常
    SmartPointer(SmartPointer<T>&& other) noexcept {
        ptr = other.ptr;
        other.ptr = nullptr;
    }

    // 拷贝赋值运算符
    SmartPointer<T>& operator=(const SmartPointer<T>& other) {
        if (this != &other) {
            delete ptr;
            ptr = new T;
            *ptr = *(other.ptr);
        }
        return *this;
    }

    // 移动赋值运算符
    // SmartPointer<int> ptr3;
    // ptr3 = std::move(ptr1); 
    // 移动赋值运算符被调用，ptr1 的资源所有权被移动给 ptr3
    //std::move()本身只是一个转换函数，它将其参数转换为右值引用，从而告诉编译器可以对其进行移动操作。std::move()并不会自动调用移动赋值运算符。
    // 在上面的例子中，std::move(ptr1)将ptr1转换为右值引用，然后将这个右值引用传递给移动赋值运算符。

    SmartPointer<T>& operator=(SmartPointer<T>&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    void show()
    {
        std::cout << *ptr << std::endl;
    }
};

int main() {
    // 创建智能指针对象
    SmartPointer<int> ptr1(new int(42));
    ptr1.show();

    // 使用移动构造函数
    SmartPointer<int> ptr2(std::move(ptr1));
    ptr2.show();

    // 使用拷贝赋值运算符
    SmartPointer<int> ptr3;
    ptr3 = ptr2;
    ptr3.show();

    // 使用移动赋值运算符
    SmartPointer<int> ptr4;
    ptr4 = std::move(ptr3);
    ptr4.show();

}
