#include "f2c.h"

#ifdef MIX_C_AND_FORTRAN
#include "f2cMang.h"
#endif

#include <time.h>

#ifdef _WIN32
#define USE_CLOCK
#endif

#ifndef USE_CLOCK
#include <sys/types.h>
#ifdef __unix__
#include <sys/times.h>
#else
struct tms { clock_t tms_utime; clock_t tms_stime; };
#define times(x) 0
#endif
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

double etime_(float* tarray)
{
#ifdef USE_CLOCK
#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC Hz
#endif
    double t = (double)clock();
    tarray[1] = 0;
    return tarray[0] = (float)(t / CLOCKS_PER_SEC);
#else
    struct tms t;
    times(&t);
    return (tarray[0] = (float)(t.tms_utime / Hz)) +
        (tarray[1] = (float)(t.tms_stime / Hz));
#endif
}
