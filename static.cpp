#include<iostream>
using namespace std;
//公共基类
class N
{
public:
    N(int data1, int data2, int data3) : 
        m_data1(data1), 
        m_data2(data2), 
        m_data3(data3)
    {
        std::cout << "call common constructor" << std::endl;
    }
    virtual ~N(){}

    void    display()
    {
        std::cout << m_data1 << std::endl;
    }

public :
    int     m_data1;
    int     m_data2;
    int     m_data3;
};


class A : virtual public N
{
public:
    A() :N(11, 12, 13), m_a(1)
    {
        std::cout << "call class A constructor" << std::endl;
    }
    ~A(){}

public :
    int m_a;
};

class B :  virtual public N
{
public:
    B() :N(21, 22, 23),m_b(2)
    {
        std::cout << "call class B constructor" << std::endl;
    }
    ~B(){}

public :
    int m_b;
};


class C : public A ,  public B
{
public:
    //负责对基类的初始化
    C() : A(), B(), N(31,32,33) ,
        m_c(3)
    {
        std::cout << "call class C constructor" << std::endl;
    }
    void show()
    {
        std::cout << "m_c=" << m_c << std::endl;
    }

 public :
    int m_c;
};

int main() {
    C instancce;

    return 0;
}
