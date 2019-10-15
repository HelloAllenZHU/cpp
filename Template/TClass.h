#ifndef TCLASS_H
#define TCLASS_H

#include<iostream>

//----------------------定义两个模板函数：add、sub
//模板函数：加法
template <class T>
T add( T a, T b ) {
    return a + b;
}

//模板函数：减法
template <class T>
T sub( T a, T b ) {
    return a - b;
}

//----------------------定义一个模板类
//模板类
template <class T>
class TClass
{
public:
    TClass();
    ~TClass();

    T add( T a, T b );
    T sub( T a, T b );
};

//构造
template <class T>
TClass<T>::TClass()
{
    std::cout << "TClass construct" << std::endl;
}

//析构
template <class T>
TClass<T>::~TClass()
{
    std::cout << "TClass destruct" << std::endl;
}

//相加运算
template <class T>
T TClass<T>::add( T a, T b ) {
    return a + b;
}

//相加运算
template <class T>
T TClass<T>::sub( T a, T b ) {
    return a - b;
}

#endif // TCLASS_H
