/*
 * 本示例演示了lambda表达式/函数的简单的用法
 * []() -> int {}
 * []表示需要捕获的外部值
 * []不捕获任何变量、[x]按值捕获x、[&x]按引用捕获x、[=]按值捕获所有变量、[&]按引用捕获所有变量、[this]按值捕获this指针
 * -> int表示返回值为int，可省略，系统会自动推导返回值类型
 * ()表示使用的参数
 * {}表示函数体
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    //使用外部变量
    int x = 1;  //按值捕获
    int y = 2;  //按引用捕获
    auto f = [ x, &y ] ( int a, int b ) mutable -> int  {
                                                                    //-> int可省略
                                                            x++;    //除非使用mutable关键字，否则此行报错
                                                            y++;    //y可读可写
                                                            return x + a + b;
                                                        };
    std::cout << f( 3, 4 ) << std::endl << y << std::endl << std::endl;

    std::vector<int> v_test{ 0, 9, 2, 7, 4, 5, 6, 3, 8, 1 };

    //没有排序因子
    std::sort( v_test.begin(), v_test.end() );
    for ( auto item: v_test ) {
        std::cout << item << std::endl;
    }
    std::cout << std::endl;

    //作为排序因子
    std::sort( v_test.begin(), v_test.end(), []( int a, int b ) {
                                                                    return a < b;
                                                                } );
    for ( auto item : v_test ) {
        std::cout << item << std::endl;
    }
    std::cout << std::endl;


    return 0;
}
