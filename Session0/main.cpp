#include <iostream>
#include <thread>
#include <functional>
#include <atomic>
#include <chrono>
#include <condition_variable>

void by_function()
{
    auto count {10};
    while(count > 0)
    {
        std::cout << "call in function \n";
        count--;
    }
    std::cout << "get thread in in function: " <<std::this_thread::get_id() << "\n";
}

class by_Operator
{
public:
    void operator()(int n)
    {
        auto count {10};
        while(n > 0)
        {
            std::cout << "call in operator \n";
            n--;
        }
    }
};

/***************************************************
 * Three way to create a thread,
 * 1. a function object
 * 2. a function pointer
 * 3. lambda function
****************************************************/
int main()
{
    std::cout <<"please add your code and have fun...\n";
    std::thread threadObj1{by_function};
    threadObj1.join();
    std::cout << "threadObj1's id " << threadObj1.get_id() << "\n";
    std::thread threadObj2{by_Operator(), 5};
    threadObj2.detach();

    std::thread threadObj3{[](int m)
                {std::cout << "From lambda "<< m <<"\n";}, 
            5};
    std::thread threadobjplus {std::move(threadObj3)};
    if (threadObj3.joinable())
    {
        std::cout << "t3 is joinable\n";
        threadObj3.join();
    }
    else
    {
        std::cout << "t3 is not joinable\n";
        threadobjplus.join();
    }
    

    auto callback = by_function;

    std::thread threadObj4{callback};
    threadObj4.detach();

    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "MainThread sleep almost " << (end - start).count() << "\n";
}
