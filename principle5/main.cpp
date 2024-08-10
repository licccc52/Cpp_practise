#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <utility>

class MyString {
private:
    char* data;
    size_t length;

public:
    // 构造函数
    MyString(const char* str) {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
        std::cout << "Constructor called." << std::endl;
    }

    // 析构函数
    ~MyString() {
        delete[] data;
        std::cout << "Destructor called." << std::endl;
    }

    // 拷贝构造函数, 没有对象, 为了构建一个新对象
    MyString(const MyString& other) {
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
        std::cout << "Copy constructor called." << std::endl;
    }

    // 拷贝赋值运算符, 已有一个对象
    MyString& operator=(const MyString& other) {
        if (this != &other) {
            delete[] data; // 删除旧资源
            length = other.length;
            data = new char[length + 1];
            strcpy(data, other.data); // 拷贝新资源
            std::cout << "Copy assignment operator called." << std::endl;
        }
        return *this;
    }

    // 移动构造函数, 没有对象,  为了构造一个新对象
    MyString(MyString&& other) noexcept {
        data = other.data;
        length = other.length;
        other.data = nullptr; // 将源对象设置为空
        other.length = 0;
        std::cout << "Move constructor called." << std::endl;
    }

    // 移动赋值运算符, 已有一个对象, 为了改变现有对象的资源
    MyString& operator=(MyString&& other) noexcept {
        if (this != &other) {
            delete[] data; // 删除旧资源
            data = other.data;
            length = other.length;
            other.data = nullptr; // 将源对象设置为空
            other.length = 0;
            std::cout << "Move assignment operator called." << std::endl;
        }
        return *this;
    }

    // 输出字符串内容
    void print() const {
        if (data) {
            std::cout << data << std::endl;
        }
    }
};

int main() {
    MyString str1 = "Hello";
    MyString str2 = str1; // 拷贝构造函数
    MyString str3("World");

    str1.print(); // 输出: Hello
    str2.print(); // 输出: Hello
    str3.print(); // 输出: World

    str3 = std::move(str1); // 移动赋值运算符
    str3.print(); // 输出: Hello
    str1.print();
    MyString str4(std::move(str3)); // hello
    str4.print();

    return 0;
}