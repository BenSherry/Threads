#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex g_mutex;
int g_sign = 0;
std::condition_variable g_cv_a;
std::condition_variable g_cv_b;
std::condition_variable g_cv_c;

void PrintA()
{
    auto count = 10;
    while(count > 0)
    {
        std::unique_lock<std::mutex> lk(g_mutex);
        while(g_sign != 1)
        { 
            g_cv_a.wait(lk, []{return g_sign == 1;});
        }
        std::cout << "This is the A...\n";
        count--;
        g_sign = 2;
        g_cv_b.notify_one();
    }
}

void PrintB()
{
    auto count = 10;
    while(count > 0)
    {
        std::unique_lock<std::mutex> lk(g_mutex);
        g_cv_b.wait(lk, []{return g_sign == 2;});
        std::cout << "This is the B...\n";
        count--;
        g_sign = 3;
        g_cv_c.notify_one();
    }
}
void PrintC()
{
    auto count = 10;
    while(count > 0)
    {
        std::unique_lock<std::mutex> lk(g_mutex);
        g_cv_c.wait(lk, []{return g_sign == 3;});
        std::cout << "This is the C...\n";
        count--;
        g_sign = 1;
        g_cv_a.notify_one();
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
    g_cv_a.notify_one();
    threadA.join();
    threadB.join();
    threadC.join();
    std::cout << "Hello, World!" << std::endl;
}
