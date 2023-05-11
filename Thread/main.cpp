/*
 * C++ 11 多线程示例代码
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <string>
#include "Create.h"
#include "Condition.h"

//**********************************************线程同步:生产者/消费者

//**********************************************std::promise/std::future异步操作
/*
 * 使用std::promise执行异步操作
 * 并且使用std::future接收返回值
 */
void func_cb( std::promise<std::string> promise, int n )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 3000 ) );
    promise.set_value( "abc" + std::to_string( n ) );
}

void FuncAsync()
{
    std::promise<std::string>   promise;
    std::future<std::string>    fr_res = promise.get_future();

    std::thread thread0( func_cb, std::move( promise ), 360 );
    //或lambda函数
    std::thread thread1( []( std::promise<std::string> *promise, int n ){
        std::this_thread::sleep_for( std::chrono::milliseconds( 3000 ) );
        promise->set_value( "abc" + std::to_string( n ) );
    }, &promise, 360 );

    std::string res = fr_res.get();
    std::cout << "res: " << res << std::endl;
    thread0.join();
    thread1.join();
}

//**********************************************std::async/std::future异步操作
/*
 * 例子：使用std::async执行异步操作
 * 并且使用std::future接收返回值
 */

/*
#include <future>

std::string func_cb( std::string prm )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 3000 ) );
    return prm + "360";
}

int main( int argc, char **argv )
{
    std::cout << "Hello world!" << std::endl;

    //std::future<std::string> fr_res = std::async( std::launch::async, func_cb, "abc" );
    //或lambda函数
    std::future<std::string> fr_res = std::async( []( std::string p ){
        std::this_thread::sleep_for( std::chrono::milliseconds( 3000 ) );
        return p + "360";
    }, "abc" );

    std::string res = fr_res.get();
    std::cout << "res: " << res << std::endl;
    return 0;
}*/


//**********************************************std::packaged_task异步操作
/*
 * 例子：使用std::packaged_task执行异步操作
 * 并且使用std::future接收返回值
 */

/*
#include <future>
#include <functional>

std::string func_cb( std::string prm )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 3000 ) );
    return prm + "360";
}

int main( int argc, char **argv )
{
    std::cout << "Hello world!" << std::endl;

    //1:线程
    std::packaged_task<std::string( std::string )> pkg0( func_cb );
    std::future<std::string> fre0 = pkg0.get_future();
    //把packaged_task对象传递到线程中异步运行
    std::thread t( std::move( pkg0 ), "abc" );
    t.join();
    //获取结果
    std::cout << "res0: " << fre0.get() << std::endl;

    //2:lambda表达式
    std::packaged_task<std::string( std::string )> pkg1( []( std::string p ){
        std::this_thread::sleep_for( std::chrono::milliseconds( 3000 ) );
        return p + "360";
    });
    pkg1( "Allen Zhu" );
    std::future<std::string> fre1 = pkg1.get_future();
    //获取结果
    std::cout << "res1: " << fre1.get() << std::endl;

    //3:bind函数
    std::packaged_task<std::string( std::string )> pkg2( std::bind( func_cb, "123"  ) );
    std::future<std::string> fre2 = pkg2.get_future();
    pkg2( "abc360_2" );
    //获取结果
    std::cout << "res2: " << fre2.get() << std::endl;
    return 0;
}*/

//**********************************************读写锁
/*
 * 例子：使用std::share_mutex执行读写锁操作
 * std::unique_lock
 */


int main(int argc, char *argv[])
{
    // 创建线程(含互斥)
    Create();

    // 条件变量
    Condition();
}
