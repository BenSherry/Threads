#include <iostream>
#include <thread>

#include "Account.hpp"

/***********************************************
 * when you want to operate more than 1 object at same time, and during this time no one can touch
 * any one of those objects, at least there is 3 ways to do this.
 * 1. in c++11, use unique_lock to lock one of object, then use std::lock to lock all of the unique_lock
 * 2. in c++17, just use scoped_lock to lock all of the objects, that make code more simple.
 * 3. in c++11, use std::lock_guard abd std::lock
************************************************/
void AccountTransfer(Account& from, Account& to, double value)
{
    std::scoped_lock lock(from.getMutex(), to.getMutex());

    /*******************************************
    std::unique_lock<std::mutex> lock1{from.getMutex(), std::defer_lock};
    std::unique_lock<std::mutex> lock2{to.getMutex(),std::defer_lock};
    std::lock(lock1, lock2);
    *******************************************/

    /******************************************
    std::lock(from.getMutex(), to.getMutex());
    std::lock_guard<std::mutex> lock1{from.getMutex(), std::adopt_lock};
    std::lock_guard<std::mutex> lock2{to.getMutex(), std::adopt_lock};
    *******************************************/

    if (from.transferOut(value))
    {
        to.transferIn(value);
    }  
}

int main()
{
    Account Bob{100};
    Account Linda{70};
    Account Tom{40};

    std::thread threadA(AccountTransfer, std::ref(Bob), std::ref(Linda), 60);
    std::thread threadB(AccountTransfer, std::ref(Bob), std::ref(Tom), 60);

    threadA.join();
    threadB.join();

    std::cout << "Bob has:" << Bob.getValue() << "\n";
    std::cout << "Linda has:" << Linda.getValue() << "\n";
    std::cout << "Tom has:" << Tom.getValue() << "\n";
}
