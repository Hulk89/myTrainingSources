//20130806 kojh : create
#ifndef _ELAPSED_TIME_HPP_
#define _ELAPSED_TIME_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
using namespace std;

class ElapsedTimer 
{
private:

    timeval startTime;

public:

    void start()
    {
        gettimeofday(&startTime, NULL);
    }

    double stop()
    {
        timeval endTime;
		double duration;
        long seconds, useconds;

        gettimeofday(&endTime, NULL);

        seconds  = endTime.tv_sec  - startTime.tv_sec;
        useconds = endTime.tv_usec - startTime.tv_usec;

        duration = seconds + useconds/1000000.0;

        return duration;
    }

    static void printElapsed( double duration )
    {
        printf("%5.6f seconds\n", duration);
    }
};
#endif
