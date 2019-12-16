#include <iostream>
#include <thread>
#include <string>

int g_ExecuteSign = 0;

void FuncPrintA()
{
    auto count = 10;
    while(count > 0)
    {
        if (1 != g_ExecuteSign)
        {
            std::this_thread::yield();
        }
        std::cout << "This is from A \n";
        count--;
        g_ExecuteSign = 2;
    }
}

void FuncPrintB()
{
    auto count = 10;
    while(count > 0)
    {
        if (2 != g_ExecuteSign)
        {
            std::this_thread::yield();
        }
        std::cout << "This is from B \n";
        count--;
        g_ExecuteSign = 3;
    }
}

void FuncPrintC()
{
    auto count = 10;
    while(count > 0)
    {
        if (3 != g_ExecuteSign)
        {
            std::this_thread::yield();
        }
        std::cout << "This is from C \n";
        count--;
        g_ExecuteSign = 1;
    }
}

int main()
{
    std::thread threadA {FuncPrintA};
    std::thread threadB {FuncPrintB};
    std::thread threadC {FuncPrintC};
    threadA.join();
    threadB.join();
    threadC.join();
    std::cout <<"please add your code and have fun...\n";
}
