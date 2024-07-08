#include <iostream>

//单例模式是指在整个系统生命周期内，保证一个类只能产生一个实例，确保该类的唯一性。
//测试

class Singleton {
public:
    // 公有静态方法，提供全局访问点，返回单例实例的引用
    static Singleton& getInstance() {
        // 在第一次调用时创建唯一实例
        // 使用静态局部变量保证线程安全性（C++11及以上版本）
        static Singleton instance;
        return instance;
    }

    // 删除拷贝构造和赋值运算符，确保单例的唯一性
    Singleton(const Singleton&) = delete;
    void operator=(const Singleton&) = delete;

    // 示例方法
    void doSomething() {
        std::cout << "doSomething() Singleton is doing something." << std::endl;
    }

private:
    // 私有构造函数，防止外部通过构造函数创建实例
    Singleton() {
        std::cout << "Constructor(): Singleton instance created." << std::endl;
    }

    // 可选：私有析构函数，确保单例对象只在程序结束时销毁
    ~Singleton() {
        std::cout << "Destructor() : Singleton instance destroyed." << std::endl;
    }
};

int main() {
    // 获取单例实例
    Singleton& instance1 = Singleton::getInstance();
    Singleton& instance2 = Singleton::getInstance();

    // 使用单例对象
    instance1.doSomething();
    instance2.doSomething();

    // 没有显示销毁单例对象，因为它在程序结束时自动销毁

    return 0;
}
