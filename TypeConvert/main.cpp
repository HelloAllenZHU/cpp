/*
 * static_cast、dynamic_cast、reinterpert_cast、const_cast
 */

#include <iostream>
#include <windows.h>

class A
{
public:
    A(){};
    virtual ~A(){};

     virtual void dosomething(){
        std::cout << "A dosomething..." << std::endl;
    };
};

class B : public A
{
public:
    B(){};
    virtual ~B(){};

     virtual void dosomething(){
        std::cout << "B dosomething..." << std::endl;
    };
};

class C : public B
{
public:
    C(){};
    virtual ~C(){};

     virtual void dosomething(){
        std::cout << "C dosomething..." << std::endl;
    };
};
/*
class D : public B, public C
{
public:
    D(){};
    virtual ~D(){};

     virtual void dosomething(){
        std::cout << "D dosomething..." << std::endl;
    };
};*/

//参考:https://www.jianshu.com/p/5163a2678171
int main()
{
    std::cout << "Hello World!" << std::endl;

    //-------------------------------------static_cast
    //基本类型转换
    int  a = 100;
    char b = static_cast<char>( a );
    std::cout << "b = " << b << std::endl;

    char   str[] = "xxx";
    LPVOID pstr1 = static_cast<LPVOID>( str );
    LPVOID pstr2 = static_cast<LPVOID>( &str );
    std::cout << "pstr1 = " << pstr1 << std::endl;
    std::cout << "pstr2 = " << pstr2 << std::endl;

    //下行(不安全，需要自己保证)
    /*A *pa0 = new A();
    B *pb0 = static_cast<B*>( pa0 );
    pb0->dosomething();

    //上行(安全)
    B *pb1 = new B();
    A *pa1 = static_cast<A*>( pb1 );
    pa1->dosomething();*/

    //-------------------------------------dynamic_cast
    //下行(安全)
    A *pa2 = new B();
    B *pb2 = dynamic_cast<B*>( pa2 );
    if ( pb2 == nullptr )
        std::cout << "pb2 is nullptr." << std::endl;
    else
        pb2->dosomething();

    //上行(安全)
    B *pb3 = new B();
    A *pa3 = dynamic_cast<A*>( pb3 );
    pa3->dosomething();

    //解锁此段代码需要修改继承关系C->A、D->BC
    /*
    D *pd4 = new D();
    //A *pa4 = dynamic_cast<A*>( pd4 ); //转换不通过，编译器不知道走D->B->A还是D->C->A路线
    B *pb4 = dynamic_cast<B*>( pd4 );   //所以通过B来转换
    A *pa4 = dynamic_cast<A*>( pb4 );
    pa4->dosomething();*/

    //-------------------------------------const_cast
    const int cc_a   = 10;
    int      *p_cc_a = const_cast<int *>( &cc_a );
    *p_cc_a          = 12;
    std::cout << "*p_cc_a = " << *p_cc_a << std::endl;
    std::cout << "cc_a    = " << cc_a << std::endl;

    int         cc_b = 100;
    const int &r_cc_b= cc_b;
    const_cast<int&>( r_cc_b ) = 102;
    std::cout << "cc_b    = " << cc_b << std::endl;
    std::cout << "r_cc_b  = " << r_cc_b << std::endl;
    return 0;
}
