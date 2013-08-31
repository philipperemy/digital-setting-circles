#include <stdbool.h>
#include <string>
#include "MathLib.h"
#include "StarData.h"
#include "Utils.h"
#include "Calc.h"


#ifndef DATA_H
#define DATA_H

class Data
{
public:

    Data(StarData& starData1, StarData& starData2);
    ~Data();

    void setTarget(double targetRA, double targetDec);

    std::string getStarName();
    void setStarName(std::string starName);

    void setEncoderResolution(int azEncoderRes, int elEncoderRes);

    void setEncoderReadRate(unsigned int encoderReadRate);

    void clearAlignmentData();

    // This reads the encoders.
    void updateCurrentAzEl(int azpos, int elpos);

    // This calls the Taki routines to calculate the target az/el
    // based on target RA/dec and the current time.
    // If needed, the flipped versions of the target az/el are also calculated.
    // No screens or forms are touched. It can be called from a periodic interrupt.
    void calculateTargetAzEl();

    // This recalculates and returns the difference between the current
    // and target az/el.
    // No screens or forms are touched.
    // It can be called from a periodic interrupt.
    // The convention is that a positive error means "go more".
    // I.e. an elevation error of +5.0, means "go up five degrees".
    // This is the opposite of some software.
    void CalculateAzElError(double *azPtr, double *elPtr);

    bool isAligned();
    void applyAlignmentData();

    double getTargetAz();
    double getTargetEl();

protected:
private:

    void setTargetAzEl(double targetAz, double targetEl);

    StarData& starData1;
    StarData& starData2;
    Calc calc;

    bool aligned;

    // Entered by user (possibly via object catalog)
    double targetRA;
    double targetDec;

    // Calculated by Taki routines from target RA/dec
    double targetAz;
    double targetEl;

    // Name of the star (refered by target RA/dec)
    std::string starName;

    unsigned int epochReference;

    int curAzCount; //Raw data from encoders
    int curElCount;

    double curAz; // Encoder counts converted to degrees
    double curEl;

    int azEncoderRes;  // Set by setup form; hardware-dependent.
    int elEncoderRes;  // Warn: If these are unsigned, some of the math goes bad.

    // Z3 is now auto-calculated
    double Z1, Z2, Z3;

    unsigned int encoderReadRate; // Samples per seconds

    int elEncoderOffset; //Set during alignement initialization ????

};


#endif // DATA_H
