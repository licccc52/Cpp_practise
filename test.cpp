#include<iostream>
using namespace std;

class Base
{
public:
    int a;
};

class Base1:virtual public Base
{
};

class Base2:virtual public Base
{
};

class Derived:public Base1,public Base2
{
private:
    double b;
public:
};

int main()
{
    cout << sizeof(Base) << endl;
    cout << sizeof(Base1) << endl;
    cout << sizeof(Base2) << endl;
    
    cout << sizeof(Derived) << endl;

    return 0;
}