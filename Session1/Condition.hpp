#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex g_mutex;
int g_sign = 0;
std::condition_variable g_cv;

void PrintA()
{
    auto count = 10;
    while(count > 0)
    {
        std::unique_lock<std::mutex> lk(g_mutex);
        g_cv.wait(lk, []{return g_sign == 1;});
        std::cout << "This is the A...\n";
        count--;
        g_sign = 2;
        g_cv.notify_one();
    }
}

void PrintB()
{
    auto count = 10;
    while(count > 0)
    {
        std::unique_lock<std::mutex> lk(g_mutex);
        g_cv.wait(lk, []{return g_sign == 2;});
        std::cout << "This is the B...\n";
        count--;
        g_sign = 3;
        g_cv.notify_one();
    }
}
void PrintC()
{
    auto count = 10;
    while(count > 0)
    {
        std::unique_lock<std::mutex> lk(g_mutex);
        g_cv.wait(lk, []{return g_sign == 3;});
        std::cout << "This is the C...\n";
        count--;
        g_sign = 1;
        g_cv.notify_one();
    }
}

void PrintABC() {
    std::thread threadA{PrintA};
    std::thread threadB{PrintB};
    std::thread threadC{PrintC};
    {
        std::unique_lock<std::mutex> lk(g_mutex);
        g_sign = 1;
    }
    g_cv.notify_all();
    threadA.join();
    threadB.join();
    threadC.join();
    std::cout << "Hello, World!" << std::endl;
}
