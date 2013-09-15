#include "Thread.h"
#include <iostream>
#include <unistd.h>
#include <sys/time.h>

#ifndef THREAD_ENCODER_H
#define THREAD_ENCODER_H

class ThreadEncoderReader : public Thread
{
public:

    ThreadEncoderReader() : Thread() { }
    virtual ~ThreadEncoderReader() { }

    virtual void run()
    {
        long u = 100000000;
        double elapsedTime = 0.0;

        struct timeval t1;
        gettimeofday(&t1, NULL);

        struct timeval t2;

        while(u > 0)
        {
            u--;
        }
        gettimeofday(&t2, NULL);

        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
        std::cout << elapsedTime << " ms.\n" << std::endl;

    }

};

#endif // THREAD_ENCODER_H
