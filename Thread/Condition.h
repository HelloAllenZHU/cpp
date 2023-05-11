/*
 * 条件变量：线程A阻塞等待条件可用，线程B设置条件可用
 * 可用于经典的"生产者-消费者"模型中
 */
#ifndef CONDITION_H
#define CONDITION_H

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex              condition_mutex;
std::condition_variable condition_variable;
std::string             condition_data;
bool ready      = false;  // 条件
bool processed  = false;  // 条件


// 工作线程
void Worker()
{
    std::unique_lock<std::mutex> lock( condition_mutex );

    // 等待主线程ready
    condition_variable.wait( lock, [] { return ready; } );

    // 等待后，继续拥有锁。
    std::cout << "工作线程正在处理数据..." << std::endl;

    // 睡眠1秒以模拟数据处理。
    std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
    condition_data += " 已处理";

    // 把数据发回主线程。
    processed = true;
    std::cout << "工作线程通知数据已经处理完毕。" << std::endl;

    // 通知前，手动解锁以防正在等待的线程被唤醒后又立即被阻塞。
    lock.unlock();

    condition_variable.notify_one();
}

// 主线程
void Condition()
{
    std::thread worker( Worker );

    // 把数据发送给工作线程。
    {
        std::lock_guard<std::mutex> lock( condition_mutex );
        std::cout << "主线程正在准备数据..." << std::endl;
        // 睡眠一秒以模拟数据准备。
        std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
        condition_data  = "样本数据";
        ready = true;
        std::cout << "主线程通知数据已经准备完毕。" << std::endl;
    }
    condition_variable.notify_one();

    // 等待工作线程处理数据。
    {
        std::unique_lock<std::mutex> lock(condition_mutex);
        condition_variable.wait(lock, [] { return processed; });
    }

    std::cout << "回到主线程，数据 = " << condition_data << std::endl;

    worker.join();
}

#endif // CONDITION_H
