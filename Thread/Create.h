/*
 * C++ 11 创建线程
 */

#ifndef CREATE_H
#define CREATE_H

#include <iostream>
#include <thread>

std::mutex  create_mutex;
int         create_count = 0;
// 线程函数
void Hello()
{
    // 加锁
    create_mutex.lock();

    std::cout << "Hello world" << std::endl;

    // 手动解锁
    create_mutex.unlock();
}

// 线程函数(带参数)
void HelloWithParam( std::string name )
{
    // 自动解锁
    std::lock_guard<std::mutex> lock( create_mutex );
    //std::unique_lock<std::mutex> lock( create_mutex );

    std::cout << "Hello " << name << std::endl;
}

// 主线程函数
void Create()
{
  // 创建子线程并立即运行
  std::thread t0( Hello );
  std::thread t1( HelloWithParam, "Allen" );
  std::thread t2( HelloWithParam, "Lucy" );

  // 等待子线程运行结束，否则主程序就退出了(子线程还没执行完)
  t0.join();
  t1.join();
  t2.join();
}

#endif // CREATE_H
