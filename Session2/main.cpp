#include <iostream>
#include <thread>
#include <string>
#include <mutex>

int g_ticket = 5;
std::mutex g_mutex;

void SaleTicketV1()
{
    while(g_ticket > 0)
    {
        /*
        lock_guard is similar with unique, all are not copyable
        the difference unique_lock is removeable, lock_guard can not
        */
        //std::lock_guard<std::mutex> lock(g_mutex);
        std::unique_lock<std::mutex> lock(g_mutex);
        std::cout << "Thread id:"<< std::this_thread::get_id() << " ticket:" << g_ticket << "\n";
        g_ticket--;
    }
}

void SaleTicketV2()
{
    while(g_ticket > 0)
    {
        g_mutex.lock();
        std::cout << "Thread id:"<< std::this_thread::get_id() << " ticket:" << g_ticket << "\n";
        g_ticket--;
        g_mutex.unlock();
    }
}

int main()
{
    std::thread ticketWindowsA{SaleTicketV1};
    std::thread ticketWindowsB{SaleTicketV1};
    ticketWindowsA.join();
    ticketWindowsB.join();
    std::cout <<"please add your code and have fun...\n";
}