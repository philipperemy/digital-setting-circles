#include "Thread.h"
#include <iostream>

#ifndef THREAD_TARGET_CALCULATOR_H
#define THREAD_TARGET_CALCULATOR_H

class ThreadTargetCalculator : public Thread
{
public:

    ThreadTargetCalculator() : Thread() { }
    virtual ~ThreadTargetCalculator() { }

    virtual void run()
    {
        long long k = 0;
        long long a = 0;
        while(true)
        {
            k = 0;
            for(int i=0;i<10000;i++)
            {
                k+=i;
            }
            k=0;
            a++;
            if(a > 10000)
            {
                std::cout << "hello I'm still here..." << std::endl;
                a = 0;
            }
        }
    }

};

#endif // THREAD_TARGET_CALCULATOR_H
