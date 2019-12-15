#pragma once

#include <iostream>
#include <mutex>

class Account{
public:
    explicit Account(double value):value_(value){};
    std::mutex& getMutex(){return mutex_;}
    double getValue(){return value_;}
    void transferIn(double value){ value_ += value;}
    bool transferOut(double value)
    {
        if (value > value_)
        {
            std::cout << "No enough money for transfer out \n";
            return false;
        }

        else
        {
            value_ -= value;
            return true;
        }
    }
private:
    double value_;
    std::mutex mutex_;
};
