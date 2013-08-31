#include <iostream>
#include "MathLib.h"
#include "Calc.h"
#include "StarData.h"
#include "Encoder.h"
#include "Test.h"

using namespace std;

int main()
{
    Test test;
    test.run_all();

  /*  Encoder encoder_1(23, 24);
    Encoder encoder_2(21, 22);

    encoderNameSpace::_callback();

    StarData starData;
    cout << "validate star data = " << starDataNamespace::validStarData(starData) << endl;

    Calc c;
    double ra = 0;
    double *raptr = &ra;
    double dec = 0;
    double *decptr = &dec;

    c.setAlignmentData(0, 200, 323, 123, 233, 2000000);
    c.setAlignmentData(1, 201, 324, 124, 234, 2000001);
    c.finalizeAlignment(false);
    c.AzElToEq(201, 122, 2000002, raptr, decptr);
    cout << "ra " << *raptr << endl;
    cout << "dec " << *decptr << endl;
    cout << "Hello world!" << endl;

    return 0;*/

}
