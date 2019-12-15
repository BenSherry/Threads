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
        std::lock_guard<std::mutex> lock(g_mutex);
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
    std::thread ticketWindowsA{SaleTicketV2};
    std::thread ticketWindowsB{SaleTicketV2};
    ticketWindowsA.join();
    ticketWindowsB.join();
    std::cout <<"please add your code and have fun...\n";
}