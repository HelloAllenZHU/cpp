#ifndef DEMO_H
#define DEMO_H

#include <iostream>

class Demo
{
public:
    Demo();
    ~Demo();

    Demo *m_p;

    //垃圾回收类
    class GC
    {
    public:
        static GC gc;

    public:
        ~GC()
        {
            std::cout << "Singleton::GC destructor" << std::endl;
        }
    };
};

#endif // DEMO_H
