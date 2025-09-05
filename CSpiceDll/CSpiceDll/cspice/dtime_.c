#include "f2c.h"
#include <time.h>

#ifdef _WIN32
#define USE_CLOCK
#else
#include <sys/types.h>
#include <sys/times.h>
#endif

#undef Hz
#ifdef CLK_TCK
#define Hz CLK_TCK
#else
#ifdef HZ
#define Hz HZ
#else
#define Hz 60
#endif
#endif

double dtime_(float* tarray)
{
#ifdef USE_CLOCK
#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC Hz
#endif
    static double t0 = 0;
    double t = (double)clock();
    tarray[1] = 0;
    tarray[0] = (float)((t - t0) / CLOCKS_PER_SEC);
    t0 = t;
    return tarray[0];
#else
    struct tms t;
    static struct tms t0 = { 0 };

    times(&t);
    tarray[0] = (float)((t.tms_utime - t0.tms_utime) / Hz);
    tarray[1] = (float)((t.tms_stime - t0.tms_stime) / Hz);
    t0 = t;
    return tarray[0] + tarray[1];
#endif
}
