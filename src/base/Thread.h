//
// Created by tiger on 2/1/23.
//

#ifndef LIBDD_THREAD_H
#define LIBDD_THREAD_H

#include <atomic>
#include <functional>
#include <memory>
#include <string>
#include <thread>

#include "noncopyable.h"

namespace libdd {
class Thread : noncopyable {
public:
    using ThreadFunc = std::function<void()>;
    using ThreadPtr = std::shared_ptr<std::thread>;
    explicit Thread(ThreadFunc func, std::string name = std::string{});
    ~Thread();

    void start() noexcept; // 开启线程
    void join() noexcept;  // 等待线程

    [[nodiscard]] bool started() const {
        return started_;
    }

    [[nodiscard]] pid_t getTid() const {
        return tid_;
    }

    [[nodiscard]] const std::string& getName() const {
        return name_;
    }

    [[nodiscard]] static int getNumCreated() {
        return numCreated_;
    }

private:
    bool started_ = false; // 是否启动线程
    bool joined_ = false;  // 是否等待该线程
    ThreadPtr thread_;
    pid_t tid_ = 0; // 线程tid
    // Thread::start() 调用的回调函数
    // 其实保存的是 EventLoopThread::threadFunc()
    ThreadFunc func_;
    std::string name_; // 线程名

    static std::atomic_int32_t numCreated_; // 线程索引
};

} // namespace libdd


#endif // LIBDD_THREAD_H
