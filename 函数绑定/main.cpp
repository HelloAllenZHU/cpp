#include <iostream>
#include <functional>
#include <stdio.h>

int funcA( int a, int b )
{
    return a + b;
}

int funcB( int &a, int &b )
{
    ++a;
    return a + b;
}

class C {
public:
    int funcC( int a, int b ) {
        return a + b;
    }
};

int main(int argc, char *argv[])
{
    // 绑定一个普通函数，传递的参数为1、2
    auto fn0 = std::bind( funcA, 1, 2 );
    std::cout << fn0() << std::endl;        // 3

    // 绑定一个普通函数，第一个参数为占位符(用于调用时传参)，第二个参数为3
    auto fn1 = std::bind( funcA, std::placeholders::_1, 3 );
    std::cout << fn1( 1 ) << std::endl;     // 4

    // 占位符是引用传递，第二个参数为值传递(虽然funcB的2个参数都为引用)
    auto a   = 1;
    auto b   = 1;
    auto fn2 = std::bind( funcB, std::placeholders::_1, b );
    std::cout << fn2( a ) << std::endl;     // 3
    std::cout << a << std::endl;            // 2    引用传递
    std::cout << b << std::endl;            // 1    值传递

    // 绑定一个类的实例函数，传递的参数为1、2
    C c;
    auto fn3 = std::bind( &C::funcC, c, 1, 2 );
    std::cout << fn3() << std::endl;        // 3

    // 绑定一个类的实例函数，参数为占位符，返回值为函数类型
    std::function<int(int,int)> fn4 = std::bind( &C::funcC, c, std::placeholders::_1, std::placeholders::_2 );
    std::cout << fn4( 1, 2 ) << std::endl;  // 3

    system( "pause" );
    return 0;
}
