#include <iostream>
#include <thread>
#include <functional>
#include <atomic>
#include <chrono>
#include <condition_variable>

class JTimer
{
public:
    JTimer(){};
    void startTimer(int interval, std::function<void()>task)
    {
        std::thread worker{[interval,task]()
            {
                while(true)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(interval));
                    task();
                }
            }
        };
        worker.detach();
    }
};

void function1()
{
    std::cout << "get thread in in function1: " <<std::this_thread::get_id() << "\n";
}

void function2()
{
    std::cout << "get thread in in function2: " <<std::this_thread::get_id() << "\n";
}

int main()
{
    JTimer t1;
    t1.startTimer(1000, std::bind(function1));
    JTimer t2;
    t2.startTimer(1000, std::bind(function2));
    while(true);
}
