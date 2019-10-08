#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    //位运算
    /*int a = 0;
    int b = a | 4;
    int c = b >> 1;
    int d = c << 1;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;*/

    //for和std::for_each
    std::vector<int> ary_xxx = { 0, 1, 2, 3, 4 };
    for ( auto item : ary_xxx ) {
        std::cout << item << std::endl;
    }

    std::for_each( ary_xxx.begin(), ary_xxx.end(), []( int &x ) {
        ++x;
    });

    for ( auto item : ary_xxx ) {
        std::cout << item << std::endl;
    }
    return 0;
}
