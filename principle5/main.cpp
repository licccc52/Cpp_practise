#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <utility>

class MyString {
private:
    char* data;
    size_t length;

public:
    // ���캯��
    MyString(const char* str) {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
        std::cout << "Constructor called." << std::endl;
    }

    // ��������
    ~MyString() {
        delete[] data;
        std::cout << "Destructor called." << std::endl;
    }

    // �������캯��, û�ж���, Ϊ�˹���һ���¶���
    MyString(const MyString& other) {
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
        std::cout << "Copy constructor called." << std::endl;
    }

    // ������ֵ�����, ����һ������
    MyString& operator=(const MyString& other) {
        if (this != &other) {
            delete[] data; // ɾ������Դ
            length = other.length;
            data = new char[length + 1];
            strcpy(data, other.data); // ��������Դ
            std::cout << "Copy assignment operator called." << std::endl;
        }
        return *this;
    }

    // �ƶ����캯��, û�ж���,  Ϊ�˹���һ���¶���
    MyString(MyString&& other) noexcept {
        data = other.data;
        length = other.length;
        other.data = nullptr; // ��Դ��������Ϊ��
        other.length = 0;
        std::cout << "Move constructor called." << std::endl;
    }

    // �ƶ���ֵ�����, ����һ������, Ϊ�˸ı����ж������Դ
    MyString& operator=(MyString&& other) noexcept {
        if (this != &other) {
            delete[] data; // ɾ������Դ
            data = other.data;
            length = other.length;
            other.data = nullptr; // ��Դ��������Ϊ��
            other.length = 0;
            std::cout << "Move assignment operator called." << std::endl;
        }
        return *this;
    }

    // ����ַ�������
    void print() const {
        if (data) {
            std::cout << data << std::endl;
        }
    }
};

int main() {
    MyString str1 = "Hello";
    MyString str2 = str1; // �������캯��
    MyString str3("World");

    str1.print(); // ���: Hello
    str2.print(); // ���: Hello
    str3.print(); // ���: World

    str3 = std::move(str1); // �ƶ���ֵ�����
    str3.print(); // ���: Hello
    str1.print();
    MyString str4(std::move(str3)); // hello
    str4.print();

    return 0;
}