/*
类型安全性：

new 和 delete 是 C++ 中的操作符，它们能够自动调用对象的构造函数和析构函数，因此对于类对象的动态分配和释放来说更加方便和类型安全。
malloc 和 free 是 C 标准库中的函数，它们只分配和释放内存块，不会调用对象的构造函数和析构函数，因此对于类对象的分配和释放需要手动管理对象的构造和析构。
返回类型：

new 返回指向分配的对象的指针，类型是对象类型的指针。
malloc 返回指向分配的内存块的指针，类型是 void*，需要进行类型转换为具体类型的指针。
大小参数：

new 和 delete 不需要指定分配的大小，编译器会根据类型自动计算大小。
malloc 和 free 需要显式指定分配的大小。
异常处理：

new 在分配内存失败时会抛出 std::bad_alloc 异常，可以使用 nothrow 版本的 new 来避免异常。
malloc 在分配内存失败时返回 nullptr，不会抛出异常。
内存对齐：

new 会自动进行内存对齐，确保返回的指针满足对象的对齐要求。
malloc 返回的指针可能不会满足对象的对齐要求，需要手动调整。
在 C++ 中，推荐使用 new 和 delete 来进行动态内存管理，因为它们更加方便、类型安全，并且能够自动调用对象的构造和析构函数。malloc 和 free 主要用于 C 语言中，或者在需要与 C 代码进行交互的情况下使用。
//
*/

#include <iostream>

class MyClass {
public:
    MyClass() {
        std::cout << "Constructor called" << std::endl;
    }

    ~MyClass() {
        std::cout << "Destructor called" << std::endl;
    }
};

int main() {
    // 使用 new 和 delete
    MyClass* obj1 = new MyClass();
    delete obj1;
    std::cout << "--------------------------" << std::endl;
    // 使用 malloc 和 free
    MyClass* obj2 = static_cast<MyClass*>(malloc(sizeof(MyClass)));
    free(obj2);

    return 0;
}
