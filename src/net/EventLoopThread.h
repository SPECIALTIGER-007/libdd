#ifndef EVENT_LOOP_THREAD_H
#define EVENT_LOOP_THREAD_H

#include <condition_variable>
#include <functional>
#include <mutex>

#include "Thread.h"
#include "noncopyable.h"

// one loop per thread
class EventLoop;
class EventLoopThread : noncopyable {
 public:
  using ThreadInitCallback = std::function<void(EventLoop *)>;

  EventLoopThread(ThreadInitCallback cb = ThreadInitCallback(),
                  const std::string &name = std::string());
  ~EventLoopThread();

  EventLoop *startLoop();  // 开启线程池

 private:
  void threadFunc();

  // EventLoopThread::threadFunc 会创建 EventLoop
  EventLoop *loop_;
  bool exiting_;
  Thread thread_;
  std::mutex mutex_;
  std::condition_variable cond_;
  ThreadInitCallback callback_;
};

#endif  // EVENT_LOOP_THREAD_H