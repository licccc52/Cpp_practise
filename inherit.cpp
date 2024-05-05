#include <iostream>
#include <utility> // 包含 std::move
#include <string>

class MyClass {
private:
    int* data;

public:
    // 默认构造函数
    MyClass() : data(nullptr) {}

    // 析构函数
    ~MyClass() {
        delete data;
    }

    // 移动构造函数
    MyClass(MyClass&& other) noexcept : data(nullptr) {
        std::cout << "移动构造函数调用" << std::endl;
        data = other.data; // 窃取资源
        other.data = nullptr; // 将原对象的资源置为空
    }

    // 移动赋值运算符
    MyClass& operator=(MyClass&& other) noexcept {
        std::cout << "移动赋值运算符调用" << std::endl;
        if (this != &other) {
            delete data; // 清理当前对象的资源
            data = other.data; // 窃取资源
            other.data = nullptr; // 将原对象的资源置为空
        }
        return *this;
    }

    // 设置数据
    void setData(int value) {
        if (!data) {
            data = new int;
        }
        *data = value;
    }

    // 获取数据
    int getData() const {
        return data ? *data : -1; // 如果 data 为空，则返回 -1
    }
};

int main() {
    MyClass obj1;
    obj1.setData(42);

    MyClass obj2 = std::move(obj1); // 使用 std::move 进行移动构造

    std::cout << "Data in obj2 after move: " << obj2.getData() << std::endl;

    MyClass obj3;
    obj3 = std::move(obj2); // 使用 std::move 进行移动赋值

    std::cout << "Data in obj3 after move assignment: " << obj3.getData() << std::endl;

    return 0;
}
