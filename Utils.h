#include <stdbool.h>
#include "StarData.h"

#ifndef UTIL_H
#define UTIL_H


class Util
{
public:

    // Calculate the difference between the angles a and b between -180 and 180 degres
    static double diff180(double a, double b);

    // Check that the two stars' az/el are not too close to one another.
    static bool goodAlignmentGeometry(StarData& starData1, StarData& starData2);

    // Return the time value to be used for calculations.
    // It is measured in minutes relative to an arbitrary epoch.
    static long long getEffectiveTime();

    static void sleep(int sleepMs);

    static void usleep(int us);

private:
    // Calculate a crude approximination of the separation between the two az/el
    // (or ra/dec) points.  The number will be a monotomically increasing with the
    // true separation, so it is good enough for sorting.  The result will range
    // from 0 to about 40000.
    static unsigned int crudeCalcSeparation(double az1, double el1, double az2, double el2);

};

#endif //UTIL_H
