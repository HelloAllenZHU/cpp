#ifndef SINGLETONTEMPLATE_H
#define SINGLETONTEMPLATE_H

/*
 * 单例模板带gc
 * 单例模式
 * 特点：
 * 1、单例类有且仅有一个实例，为了避免被外界创建多个对象，所以构造函数必须为私有，赋值操作符也不能被外界调用
 * 2、单例类必须自己创建该唯一实例，所以该类包含一个private static * instance
 * 3、单例类必须给外界提供一个访问该唯一实例的入口，例如public static * GetInstance
 */

#include <iostream>

template <class T>
class Singleton : public T
{
private:
    // 默认构造函数
    Singleton();

    // 拷贝构造函数
    Singleton( const Singleton & ); // 无需实现

    // 重载赋值操作符(禁止赋值)
    Singleton & operator = ( const Singleton & ); // 无需实现

    // 析构函数(只是用于验证垃圾回收是否有效)
    ~Singleton() {}

public:
    // 返回唯一实例
    static T * GetInstance() {
        if ( m_pInstance == nullptr )
            m_pInstance = new T;

        return m_pInstance;
    }

private:
    static T * m_pInstance;

public:
    // 垃圾回收类
    class GC
    {
    private:
        static GC gc;

    public:
        ~GC()
        {
            if ( m_pInstance != nullptr ) {
                std::cout << "Singleton<T>::GC Grabber destruct..." << std::endl;
                delete m_pInstance;
                m_pInstance = nullptr;
            }
        }
    };
};


//饿汉式：程序启动时就创建，优点：简单、线程安全，缺点：提前占用内存
/*template <class T>
T *   Singleton<T>::m_pInstance = new T;*/

//懒汉式：Qt窗口必须在QApplication实例之后创建
template <class T>
T *   Singleton<T>::m_pInstance = nullptr;

//声明垃圾回收对象(声明之后会析构gc，gc会释放单例对象，未声明则不会)
template <class T>
class Singleton<T>::GC Singleton<T>::GC::gc;

#endif // SINGLETONTEMPLATE_H
