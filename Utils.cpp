#include <time.h>

#include "Utils.h"
#include "MathLib.h"
#include "Calc.h"

///TO BE CHANGED AT COMPILE TIME
#define LINUX OK

#ifdef LINUX
#include <unistd.h>
#endif // LINUX
#ifdef WINDOWS
#include<windows.h>
#endif // WINDOWS


double Util::diff180(double a, double b)
{
  double diff = a - b;

  while (diff <= -180.0)
  {
    diff += 360.0;
  }

  while (diff > 180.0)
  {
    diff -= 360.0;
  }

  return diff;
}

unsigned int Util::crudeCalcSeparation(double az1, double el1, double az2, double el2)
{
    double cossep;

    az1 *= radPerDeg;
    el1 *= radPerDeg;
    az2 *= radPerDeg;
    el2 *= radPerDeg;

    cossep = (MathLib::sin(el1)*MathLib::sin(el2)) + (MathLib::cos(el1)*MathLib::cos(el2)*MathLib::cos(az1-az2));

    return (unsigned int)(20000.0*(1.0-cossep));
}

bool Util::goodAlignmentGeometry(StarData& starData1, StarData& starData2)
{
    unsigned int crudeSep, minCrudeSep;
    double azDiff;

    // Reject alignments with insufficient separation in azimuth, even if the
    // elevations are quite different.

    azDiff = diff180(starData1.az, starData2.az);

    if (fabs(azDiff) < 5.0)
    {
        return false;
    }

    // Also make sure the recorded az/el positions are not identical
    // or very close to each other.
    minCrudeSep = crudeCalcSeparation(0.0, 0.0, 0.0, 5.0);  // 5.0 degree min sep

    crudeSep = crudeCalcSeparation(starData1.az, starData1.el, starData2.az, starData2.az);

    if (crudeSep < minCrudeSep)
    {
        return false;
    }

    return true;
}

//Time since 00:00 Jan 1, 2000 UTC
long long Util::getEffectiveTime()
{
    time_t timer;
    struct tm y2k;
    double seconds;

    y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
    y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

    time(&timer);  /* get current time; same as: timer = time(NULL)  */
    seconds = difftime(timer,mktime(&y2k));
    return seconds;
}

void Util::sleep(int sleepMs)
{
    #ifdef LINUX
        usleep(sleepMs * 1000);   // usleep takes sleep time in us
    #endif
    #ifdef WINDOWS
        Sleep(sleepMs);
    #endif
}

void Util::usleep(int sleepUs)
{
    #ifdef LINUX
        ::usleep(sleepUs);   // usleep takes sleep time in us
    #endif
}

