/*
 * 智能指针
 * auto_ptr:   所有权策略(策略不严格，运行出错)
 * unique_ptr: 所有权策略(策略严格，编译出错)
 * shared_ptr: 引用且计数策略(存在循环计数的问题，会死锁)
 * weak_ptr:   引用不计数策略(不会死锁)
 * 以上智能指针的构造函数都生命为explicit，因此必须显示调用，使用=隐式构造将不被允许
 */

#include <iostream>
#include <memory>

using namespace std;

//不使用智能指针
void test0() {
    int *p = new int;
    *p = 0;

    std::cout << "test0:" << *p << std::endl;
    delete p;
}

//std::auto_ptr: 会发生所有权转让，再次使用原指针会报错，运行时才报错
//auto_ptr只能与new一起使用，不能与new[]一起使用（share_ptr同样）
void test1() {
    std::auto_ptr<int> p( new int() );
    *p.get() = 1;  //p.get() 将返回原始指针

    /* p的所有权转让给p1了，p.get()将返回空指针，再次使用p将会出错，
     * p对该对象的所有权被剥夺，避免了析构时系统重复释放同一个对象
     */
    //std::auto_ptr<int> p1 = p;
    std::cout << "test1:" << *p.get() << std::endl;
}

//std::unique_ptr: 会发生所有权转让，再次使用原指针会报错，编译时才报错
//unique_ptr可以使用new，也可以使用new[]
void test2() {
    std::unique_ptr<int> p( new int() );
    *p.get() = 2;  //p.get() 将返回原始指针

    /* 将p的所有权转让给p1，由于unique_ptr策略严格，编译时将直接报错，
     * 不会等到运行时再去报错，这样就避免了低级、潜在的bug
     */
    //std::unique_ptr<int> p1 = p;              //此处直接报错
    //std::unique_ptr<int> p2 = std::move( p ); //此处不报错，转移所有权，现在那块内存由p2接管，p.get（）依然返回空指针
    std::cout << "test2:" << *p.get() << std::endl;
}

//std::shared_ptr
void test3() {
    std::shared_ptr<int> p( new int() );
    *p.get() = 3;  //p.get() 将返回原始指针

    /* shared_ptr采用了引用计数策略，p和p1都是指向了同一个对象，
     * 该对象的引用计数为0时，将自动释放掉该对象
     */
    std::shared_ptr<int> p1 = p;    //此处不会报错
    std::cout << "test3:" << *p.get() << std::endl;

    //下面的代码是问题：相互引用(死锁)
    /*
        std::shared_ptr<int> p2( new int() );
        p2 = p1;
        p1 = p2;
    */
}

//std::weak_ptr
void test4() {
    std::shared_ptr<int> p1(new int(5));
    std::weak_ptr<int> wp1 = p1; // 还是只有p1有所有权。
    {
      std::shared_ptr<int> p2 = wp1.lock(); // p1和p2都有所有权
      if (p2) // 使用前需要检查
      {
        // 使用p2
      }
    } // p2析构了，现在只有p1有所有权。

    p1.reset(); // 内存被释放。

    std::shared_ptr<int> p3 = wp1.lock(); // 因为内存已经被释放了，所以得到的是空指针。
    if ( p3 )
    {
      // 不会执行到这。
    }
}
int main()
{
    cout << "Hello World!" << endl;

    test0();
    test1();
    test2();
    test3();
    return 0;
}
