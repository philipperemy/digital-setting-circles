#include "Data.h"


#include <cmath>


Data::Data(StarData& starData1, StarData& starData2)
: starData1(starData1), starData2(starData2),
epochReference(0), elEncoderOffset(0)
{
    //ctor
    curAz = NAN;
    curEl = NAN;

    aligned = false;

    targetRA = 0.0;
    targetDec = 0.0;

    targetAz = NAN;
    targetEl = NAN;

    //Avoid diving by 0
    azEncoderRes = 8192;

    Z1 = 0.0;
    Z2 = 0.0;
    Z3 = 0.0;

    //Default is 10
    encoderReadRate = 10;
}

void Data::applyAlignmentData()
{
    if(starDataNamespace::validAlignementData(starData1, starData2))
    {
        aligned = true;
    }
}

void Data::setTarget(double targetRA, double targetDec)
{
    this->targetRA = targetRA;
    this->targetDec = targetDec;

}

void Data::setTargetAzEl(double targetAz, double targetEl)
{
    this->targetAz = targetAz;
    this->targetEl = targetEl;
}

Data::~Data()
{
    //dtor
}

double Data::getTargetAz()
{
    return targetAz;
}

double Data::getTargetEl()
{
    return targetEl;
}

bool Data::isAligned()
{
    return aligned;
}

std::string Data::getStarName()
{
    return starName;
}

void Data::setStarName(std::string starName)
{
    this->starName = starName;
}

void Data::setEncoderResolution(int azEncoderRes, int elEncoderRes)
{
    this->azEncoderRes = azEncoderRes;
    this->elEncoderRes = elEncoderRes;
}

void Data::setEncoderReadRate(unsigned int encoderReadRate)
{
    this->encoderReadRate = encoderReadRate;
}

void Data::clearAlignmentData()
{
    starDataNamespace::clearAlignmentData(starData1, starData2);
}

void Data::updateCurrentAzEl(int azpos, int elpos)
{
    curAzCount = azpos;
    curElCount = elpos;

    // Get the az value into the 0 .. res-1 range
    while (azpos >= azEncoderRes)
    {
        azpos -= azEncoderRes;
    }

    while (azpos < 0)
    {
        azpos += azEncoderRes;
    }

    // Convert az to 0..360.0 range
    curAz = (double)azpos / azEncoderRes * 360.0;

    // Apply the elevation zero correction that was established during
    // encoder reset.
    elpos -= elEncoderOffset;

    while (elpos >= (elEncoderRes/2))
    {
      elpos -= elEncoderRes;
    }

    while (elpos < -(elEncoderRes/2))
    {
      elpos += elEncoderRes;
    }

    curEl = (double)elpos / elEncoderRes * 360.0;
}

void Data::calculateTargetAzEl()
{
    targetAz = NAN;
    targetEl = NAN;

    // If we have valid alignment data,
    // recalculate everything based on the current position and time,
    // and update the form's result fields.

    if(isAligned() && finite(targetRA) && finite(targetDec))
    {
        calc.EqToAzEl(targetRA, targetDec, Util::getEffectiveTime(),
	      false, &targetAz, &targetEl);

        setTargetAzEl(targetAz, targetEl);
    }
}

void Data::CalculateAzElError(double *azPtr, double *elPtr)
{
    double azErr, elErr;

    if (finite(curAz) &&
        finite(curEl) &&
        finite(targetAz) &&
        finite(targetEl)) {

            azErr = Util::diff180(targetAz, curAz);
            elErr = Util::diff180(targetEl, curEl);

      } else {

            azErr = NAN;
            elErr = NAN;
      }

    //If pointers are not NULL, affect them
    if (azPtr)
    {
        *azPtr = azErr;
    }
    if (elPtr)
    {
        *elPtr = elErr;
    }
}
