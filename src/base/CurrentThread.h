#ifndef CURRENT_THREAD_H
#define CURRENT_THREAD_H

#include <sys/syscall.h>
#include <unistd.h>

namespace libdd::CurrentThread {

extern __thread int t_cachedTid; // 保存tid缓冲，避免多次系统调用
void cacheTid();

// 内联函数
inline int tid() {
    if (__builtin_expect(t_cachedTid == 0, 0)) {
        cacheTid();
    }
    return t_cachedTid;
}
} // namespace CurrentThread

#endif // CURRENT_THREAD_H