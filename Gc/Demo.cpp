#include <iostream>
#include "Demo.h"

//声明之后，才能实现自动GC
Demo::GC Demo::GC::gc;

Demo::Demo()
{
    std::cout << "Demo constructor" << std::endl;
    m_p = this;
}

Demo::~Demo()
{
    std::cout << "Demo destructor" << std::endl;
}
