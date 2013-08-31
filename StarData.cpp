#include "StarData.h"

StarData::StarData()
{
    //ctor
    az = NAN;
    el = NAN;
    ra = NAN;
    dec = NAN;
    time = 0.0;
}

StarData::~StarData()
{
    //dtor
}

void StarData::clearData()
{
    az = NAN;
    el = NAN;
    time = 0.0;
}
