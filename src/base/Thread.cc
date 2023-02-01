//
// Created by tiger on 2/1/23.
//

#include "Thread.h"

#include <semaphore.h>

#include <memory>
#include <utility>

#include "CurrentThread.h"

namespace libdd {
std::atomic_int32_t Thread::numCreated_(0);

Thread::Thread(Thread::ThreadFunc func, std::string name)
    : func_(std::move(func)), // EventLoopThread::threadFunc()
      name_(std::move(name)) {
    int num = ++numCreated_;
    if (name_.empty()) {
        char buf[32] = {0};
        snprintf(buf, sizeof(buf), "Thread%d", num);
        name_ = buf;
    }
}

Thread::~Thread() {
    // 现场感启动时并且未设置等待线程时才可调用
    if (started_ && !joined_) {
        // 设置线程分离(守护线程，不需要等待线程结束，不会产生孤儿线程)
        thread_->detach();
    }
}

void Thread::start() noexcept {
    started_ = true;
    sem_t sem;
    sem_init(&sem, false, 0);
    // 开启线程
    thread_ = std::make_shared<std::thread>([this, &sem]() {
        // 获取线程tid
        tid_ = CurrentThread::tid();
        // 开启一个新线程专门执行该线程函数
        func_();
        // v操作
        sem_post(&sem);
    });

    /**
     * 这里必须等待获取上面新创建的线程的tid
     * 未获取到信息则不会执行sem_post，所以会被阻塞住
     * 如果不使用信号量操作，则别的线程访问tid时候，可能上面的线程还没有获取到tid
     */
    sem_wait(&sem);
}

void Thread::join() noexcept {
    joined_ = true;
    // 等待线程执行完毕
    thread_->join();
}

} // namespace libdd
