//
// Created by tiger on 2/1/23.
//
/**
 * confirm the func_ subsequence between the whole life of thread.
 */
#include "Thread.h"

#include <iostream>

int main() {
    std::cout << "thread construct" << std::endl;
    libdd::Thread thread{[] {
                             std::cout << "这是回调函数" << std::endl;
                         },
                         "thread1"};
    std::cout << "-------------" << std::endl;
    std::cout << "thread start" << std::endl;
    thread.start();
    std::cout << "-------------" << std::endl;
    std::cout << "thread join" << std::endl;
    thread.join();
    std::cout << "-------------" << std::endl;
    std::cout << "thread deconstruct" << std::endl;
}