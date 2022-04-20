/*
 * C++ 11 多线程
 * 创建/销毁线程、传递参数/获取结果、线程同步/互斥
 *
 */

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

//**********************************************创建线程

//**********************************************传递参数(未完成)
/*
 * 例子1：传递参数给子线程
 */
/*
int         p = 0;
std::mutex  mtx;

//线程函数
void t_cb() {
    while ( true ) {
        //加锁
        mtx.lock();

        if ( p >= 100 )
            break;
        else
            std::cout << ++p << std::endl;

        //解锁
        mtx.unlock();
    }
}

//线程函数
void t_cb2() {
    while ( true ) {
        //定义lock变量时自动加锁，lock变量的生命周期结束时自动解锁
        std::lock_guard<std::mutex> lock( mtx );

        if ( p >= 100 )
            break;
        else
            std::cout << ++p << std::endl;
    }
}

int main()
{
    std::thread t0( t_cb );
    std::thread t1( t_cb );

    t0.join();
    t1.join();

    cout << "Hello World!: " << p << endl;
    return 0;
}*/

//**********************************************线程同步:互斥
/*
 * 例子1：使用std::mutex实现线程同步
 */
/*
int         p = 0;
std::mutex  mtx;

//线程函数
void t_cb() {
    while ( true ) {
        //加锁
        mtx.lock();

        if ( p >= 100 )
            break;
        else
            std::cout << ++p << std::endl;

        //解锁
        mtx.unlock();
    }
}

int main()
{
    std::thread t0( t_cb );
    std::thread t1( t_cb );

    t0.join();
    t1.join();

    cout << "Hello World!: " << p << endl;
    return 0;
}*/


/*
 * 例子2：使用std::lock_guard实现线程同步
 */
/*
int         p = 0;
std::mutex  mtx;

//线程函数
void t_cb() {
    while ( true ) {
        //使用std::lock_guard，以避免忘记调用std::lock.unlock，在lg的生命周期结束的时候，会在析构函数里面调用std::lock.unlock
        std::lock_guard<std::mutex> lg( mtx );

        if ( p >= 100 )
            break;
        else
            std::cout << ++p << std::endl;
    }
}

int main()
{
    std::thread t0( t_cb );
    std::thread t1( t_cb );

    t0.join();
    t1.join();

    cout << "Hello World!: " << p << endl;
    return 0;
}
*/

//**********************************************线程同步:生产者/消费者(未完成)
/*
 * 例子：使用std::mutex实现线程同步
 */

/*
#include <condition_variable>

int         p = 0;
std::mutex  mtx;

//线程函数
void t_cb() {
    while ( true ) {
        //加锁
        mtx.lock();

        if ( p >= 100 )
            break;
        else
            std::cout << ++p << std::endl;

        //解锁
        mtx.unlock();
    }
}

int main()
{
    std::thread t0( t_cb );
    std::thread t1( t_cb );

    t0.join();
    t1.join();

    cout << "Hello World!: " << p << endl;
    return 0;
}*/


//**********************************************std::promise/std::future异步操作
/*
 * 例子：使用std::promise执行异步操作
 * 并且使用std::future接收返回值
 */

/*
#include <future>

void func_cb( std::promise<std::string> pms, int n )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( 3000 ) );
    pms.set_value( "abc" + std::to_string( n ) );
}

int main( int argc, char **argv )
{
    std::cout << "Hello world!" << std::endl;

    std::promise<std::string> pms;
    std::future<std::string> fr_res = pms.get_future();

    std::thread t( func_cb, std::move( pms ), 360 );
    //或lambda函数
    std::thread t2( []( std::promise<std::string> *p_pms, int n ){
        std::this_thread::sleep_for( std::chrono::milliseconds( 3000 ) );
        p_pms->set_value( "abc" + std::to_string( n ) );
    }, &pms, 360 );

    std::string res = fr_res.get();
    std::cout << "res: " << res << std::endl;
    t.join();
    return 0;
}*/


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

///*
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
}//*/

//**********************************************读写锁
/*
 * 例子：使用std::share_mutex执行读写锁操作
 * std::unique_lock
 */

