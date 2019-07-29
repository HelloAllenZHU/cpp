#include <iostream>

using namespace std;

/*对于 C++ 的类，如果程序员没有为其定义特殊成员函数，那么
 *在需要用到某个特殊成员函数的时候，编译器会隐式的自动生成
 *一个默认的特殊成员函数，比如拷贝构造函数，或者拷贝赋值操作符
 */
class A {
public:
    //默认构造(若未定义，则编译器会自动隐式生成)
    //A() {};
    /*
     * 编译器将为声明为default的函数自动生成函数体，
     * 该函数体的执行效率高于用户自定义的默认函数体
     */
    A() = default;

    virtual ~A() = default; //定义成default

    //析构函数(若未定义，则编译器会自动隐式生成)
    //virtual ~A() {};

    //拷贝构造(若未定义，则编译器会自动隐式生成)
    A( const A & a ) = delete;  //delete关键字，表示禁止系统自动生成拷贝构造函数

    //拷贝赋值(若未定义，则编译器会自动隐式生成)
    A & operator = ( const A & a ) = delete;//delete关键字，表示禁用该函数
};

int main()
{
    cout << "Hello World!" << endl;

    A a;        //已经定义了拷贝构造函数，编译器不再生成默认构造函数，所以此处报错
    A b( a );   //调用拷贝构造，但其被声明为delete，不能使用copy语义，需定义移动构造
    A c;        //调用默认构造
    c= b;       //调用拷贝赋值，但其被声明为delete，不能使用copy语义，需重载移动赋值
    return 0;
}
