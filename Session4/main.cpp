#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <functional>

void doSomeThing(std::promise<int> doSomething_promise)
{
    std::cout << "start do some lomg time work, be patient......\n";
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "For the sake of the god, every thing is done......\n";
    doSomething_promise.set_value(99);
}

int main()
{
    std::promise<int> doSomething_Promise;
    auto result = doSomething_Promise.get_future();
    std::thread threadDoSomeThing{doSomeThing, std::move(doSomething_Promise)};
   
    threadDoSomeThing.join();
    std::cout <<"get result:" << result.get() << "\n" ;

    std::packaged_task<int(int, int)>taskadd {
        [](int a, int b)
        {
            return a + b;
        }
    };

    auto addPrsult = taskadd.get_future();
    taskadd(9 , 8);
    std::cout << "add task "<< addPrsult.get() << "\n";
    
    std::packaged_task<int(int, int)>taskadd1 {
        [](int a, int b)
        {
            return a + b;
        }
    };
    auto threadAdd = taskadd1.get_future();
    std::thread threadTask{std::move(taskadd1), 13, 14};

    threadTask.join();
    std::cout << "Thread task:" << threadAdd.get() << "\n";
}
