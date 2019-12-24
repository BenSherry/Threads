#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <functional>
#include <mutex>

std::mutex g_mutex; // for print log

void doSomeThing(std::shared_future<int> doSomething_future, int num)
{

    std::unique_lock<std::mutex> lk(g_mutex);
    std::cout << "func " << num << " dosomething wait signal \n";
    doSomething_future.wait();
    std::cout << "signal is ready, it is " << doSomething_future.get() << "\n";
}

int main()
{
    std::promise<int> doSomething_Promise;
    std::shared_future<int>  result = doSomething_Promise.get_future();
    std::thread threadDoSomeThing1{doSomeThing, result, 1};
    std::thread threadDoSomeThing2{doSomeThing, result, 2};
    doSomething_Promise.set_value(100);
   
    threadDoSomeThing1.join();
    threadDoSomeThing2.join();
}
