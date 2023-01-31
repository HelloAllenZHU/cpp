#include <iostream>
#include <vector>
#include <functional>
#include <stdio.h>

int main(int argc, char *argv[])
{
    // 左值引用
    int a   = 1;
    int &ra = a;
    std::cout << ra << std::endl;

    // 右值引用
    int &&rb = 2;
    rb = 3;
    std::cout << rb << std::endl;

    // 右值引用指向左值
    int &&rc = std::move( a );  // 把左值转换为右值
    std::cout << rc << std::endl;

    // 移动之后，str字符串丢失数据，变为空
    std::string str = "Hello";
    std::vector<std::string> vt;
    vt.push_back( std::move( str ) );
    std::cout << str << std::endl;

    system( "pause" );
    return 0;
}
