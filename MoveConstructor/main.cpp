/*
 * C++11
 * 移动构造函数、移动赋值操作符
 */

#include <iostream>

using namespace std;

class Test
{
public:
    //默认构造
    Test()
    {
        a = 100;
        b = 200;
    }

    //拷贝构造
    Test( const Test & t )
    {
        this->a = t.a;
        this->b = t.b;
    }

    //拷贝赋值操作符
    Test & operator=( const Test & t )
    {
        if ( this != &t ) {
            this->a = t.a;
            this->b = t.b;
        }

        return *this;
    }

    //移动构造
    Test( Test &&t )
    {
        this->a = t.a;
        this->b = t.b;
        t.a = 0;
        t.b = 0;
    }

    //移动赋值操作符
    Test & operator=( Test && t )
    {
        if ( this != &t ) {
            this->a = t.a;
            this->b = t.b;
            t.a = 0;
            t.b = 0;
        }

        return *this;
    }

private:
    int a;
    int b;
};

int main( int argc, char **argv )
{
    Test a;                     //默认构造

    Test b( a );                //拷贝构造

    Test c;
    c = b;                      //拷贝赋值

    Test d( std::move( c ) );   //移动构造

    Test e;
    c = std::move( d );         //移动赋值

    std::cout << "Hello world!" << std::endl;
    return 0;
}
