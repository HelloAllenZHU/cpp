#include <iostream>

using namespace std;

class A //final
{
public:
    A() {}
    virtual ~A() {}

    virtual void dosomething() /*final*/ {
        std::cout << "A::dosomething" << std::endl;
    }
};

class B : public A  //如果A定义为final，此处会报错
{
public:
    B() {}
    ~B() {}

    //如果A::dosomething定义为final，此处会报错
    virtual void dosomething() {
        std::cout << "B::dosomething" << std::endl;
    }
};

class C
{
public:
    C() {}
    virtual ~C() {}

    virtual void dosomething() {
        std::cout << "C::dosomething" << std::endl;
    }
};

class D : public C
{
public:
    D() {}
    ~D() {}

    //此处使用override，表示是重写父类的dosomething函数，
    //编译器会检查父类中是否有返回类型、函数名、参数类型完全相同的虚函数
    virtual void dosomething() override {
        std::cout << "D::dosomething" << std::endl;
    }

    //此处没使用override，表示是子类自己新定义的虚函数
    virtual void dosomething2() {};
};

int main()
{
    cout << "Hello World!" << endl;

    A *a = new B();
    a->dosomething();

    C *c = new D();
    c->dosomething();
    return 0;
}
