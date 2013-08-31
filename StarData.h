#include <stdbool.h>
#include "MathLib.h"
#include <cmath>

#ifndef STARDATA_H
#define STARDATA_H

class StarData
{
public:
    StarData();
    ~StarData();
    int index;   // Identifies star in data list
    double az, el;  // Set by user or encoders
    double ra, dec;  // From star data list
    double time;  // Set to current time (minutes) when az/el is set

    void clearData();

};

namespace starDataNamespace
{
    // Check that all values have been meaningfully defined.
    // An undefined value will have been initialized to NaN.
    static bool validStarData(StarData& sd)
    {
      return (  MathLib::finite(sd.ra) &&
                MathLib::finite(sd.dec) &&
                MathLib::finite(sd.az) &&
                MathLib::finite(sd.el) &&
                sd.time >= 0.0 &&
                sd.ra >= 0.0);
    }

    // Check that both stars are defined, and they are not
    // the same star.
    static inline bool validAlignementData(StarData& starData1, StarData& starData2)
    {
        return  starDataNamespace::validStarData(starData1) &&
                starDataNamespace::validStarData(starData2) &&
                &starData1 != &starData2;
    }

    static inline void clearAlignmentData(StarData& starData1, StarData& starData2)
    {
        starData1.clearData();
        starData2.clearData();
    }

}



#endif // STARDATA_H
