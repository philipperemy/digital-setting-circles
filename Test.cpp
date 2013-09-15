#include <iostream>

#include "Test.h"
#include "TestCase.h"
#include "Utils.h"
#include "MathLib.h"
#include "Calc.h"
#include "Encoder.h"
#include "Data.h"
#include "Object.h"
#include "Thread.h"

#include <time.h>

#include "ThreadEncoderReader.h"
#include "ThreadTargetCalculator.h"

#define pi 3.14159265358979323846
#define INFINITY_POSITIVE 1000000000.0
#define INFINITY_NEGATIVE -1000000000.0

void Test::run_all()
{
    try
    {
        //test_Thread();
        test_StarData();
        test_StarDataNamespaceFunctions();
        test_MathLib_trigonometric();
        test_MathLib_exponential_logarithmic();
        test_MathLib_hyperbolic();
        test_power();
        test_nearest_absolute_remainder();
        test_miscellaneous();
        test_Util();
        test_Encoder();
        test_Data();
        test_Object();
    }
    catch(const std::exception& fail)
    {
        std::cerr << fail.what() << std::endl;
    }
}

void Test::test_Thread()
{
    Thread * t = new ThreadEncoderReader();
    Thread * t2  = new ThreadTargetCalculator();
    t->start();
    t2->start();
    t->join();
    t2->join();
    delete(t);
    delete(t2);
}

void Test::test_StarDataNamespaceFunctions()
{
    setUpErrorMessage("test_StarDataNamespaceFunctions() - failed");

    StarData starData1;
    StarData starData2;

    starData1.az = 1;
    starData1.el = 2;
    starData1.ra = 3;
    starData1.dec = 4;
    starData1.time = 5;

    starData2.az = 1;
    starData2.el = 2;
    starData2.ra = 3;
    starData2.dec = 4;
    starData2.time = 5;

    assertTrue(starDataNamespace::validStarData(starData1));
    assertTrue(starDataNamespace::validStarData(starData2));

    assertTrue(starDataNamespace::validAlignementData(starData1, starData2));

    starDataNamespace::clearAlignmentData(starData1, starData2);

    assertTrue(!starDataNamespace::validAlignementData(starData1, starData2));
}

void Test::test_StarData()
{
    setUpErrorMessage("test_ValidateStarData() - failed");

    StarData starData;

    assertTrue(!starDataNamespace::validStarData(starData));

    assertNan(starData.az);
    assertNan(starData.el);
    assertNan(starData.ra);
    assertNan(starData.dec);
    assertNan(starData.time);
    assertEquals(0.0, starData.time);

    starData.az = 1;
    starData.el = 2;
    starData.ra = 3;
    starData.dec = 4;
    starData.time = 5;

    assertTrue(starDataNamespace::validStarData(starData));

    assertEquals(1.0, starData.az);
    assertEquals(2.0, starData.el);
    assertEquals(3.0, starData.ra);
    assertEquals(4.0, starData.dec);
    assertEquals(5.0, starData.time);

    starData.clearData();

    assertTrue(!starDataNamespace::validStarData(starData));

    assertNan(starData.az);
    assertNan(starData.el);
    assertEquals(3.0, starData.ra);
    assertEquals(4.0, starData.dec);
    assertNan(starData.time);
    assertEquals(0.0, starData.time);

}

void Test::test_MathLib_trigonometric()
{
    setUpErrorMessage("test_MathLib_trigonometric() - failed");

    assertEquals(1.0, MathLib::cos(0));
    assertEquals(0.0, MathLib::sin(0));

    assertEquals(MathLib::sqrt(2)/2, MathLib::cos(pi/4));
    assertEquals(MathLib::sqrt(2)/2, MathLib::sin(pi/4));

    assertEquals(0.0, MathLib::cos(pi/2));
    assertEquals(1.0, MathLib::sin(pi/2));

    assertEquals(-1.0, MathLib::cos(pi));
    assertEquals(0.0, MathLib::sin(pi));

    assertEquals(0.0, MathLib::cos(3*pi/2));
    assertEquals(-1.0, MathLib::sin(3*pi/2));

    assertEquals(1.0, MathLib::cos(2*pi));
    assertEquals(0.0, MathLib::sin(2*pi));

    //tan
    assertEquals(0.0, MathLib::tan(0));
    assertEquals(1.0, MathLib::tan(pi/4));
    assertGreater(INFINITY_POSITIVE, MathLib::tan(pi/2));
    assertLess(INFINITY_NEGATIVE, MathLib::tan(-pi/2));

    //acos
    assertEquals(0.0, MathLib::acos(1));
    assertEquals(pi/2, MathLib::acos(0));
    assertEquals(pi, MathLib::acos(-1));
    assertEquals(pi/4, MathLib::acos(MathLib::sqrt(2)/2));

    //asin
    assertEquals(0.0, MathLib::asin(0));
    assertEquals(pi/2, MathLib::asin(1));
    assertEquals(-pi/2, MathLib::asin(-1));
    assertEquals(pi/4, MathLib::asin(MathLib::sqrt(2)/2));

    //atan
    assertEquals(0.0, MathLib::atan(0.0));
    assertEquals(pi/4, MathLib::atan(1.0));
    assertEquals(pi/2, MathLib::atan(INFINITY_POSITIVE));
    assertEquals(-pi/2, MathLib::atan(INFINITY_NEGATIVE));

    double atan_X = MathLib::atan(0.2);
    double atan_Y = MathLib::atan(0.3);
    double atan_XY = MathLib::atan((0.2+0.3)/(1-0.2*0.3));
    assertEquals(atan_X+atan_Y, atan_XY);

    assertEquals(MathLib::atan(0.0), MathLib::atan2(0.0, 1.0));
    assertEquals(MathLib::atan(1.0), MathLib::atan2(1.0, 1.0));
    assertEquals(MathLib::atan(INFINITY_POSITIVE), MathLib::atan2(1.0, 0.0));
}

void Test::test_MathLib_exponential_logarithmic()
{
    setUpErrorMessage("test_MathLib_exponential_logarithmic() - failed");

    assertEquals(0.0, MathLib::exp(INFINITY_NEGATIVE));
    assertEquals(1.0, MathLib::exp(0));
    assertEquals(2.71828, MathLib::exp(1));
    assertEquals(22026.46579, MathLib::exp(10));
    assertEquals(33.0, MathLib::exp(MathLib::log(33)));
    assertEquals(44.0, MathLib::log(MathLib::exp(44)));

    assertEquals(1.0, MathLib::log(2.71828));
    assertEquals(0.0, MathLib::log(1.0));
    assertLess(INFINITY_POSITIVE, MathLib::log(INFINITY_POSITIVE));
    assertLess(INFINITY_NEGATIVE, MathLib::log(0));

    assertEquals(22026.46579-1, MathLib::expm1(10));
    assertEquals(0.0, MathLib::log1p(0));
    assertEquals(1.0, MathLib::log1p(2.71828-1));

    assertEquals(MathLib::log(10) / MathLib::log(2), MathLib::log2(10));
    assertEquals(3.0, MathLib::log2(MathLib::pow(2,3)));

    assertEquals(MathLib::log(12) / MathLib::log(10), MathLib::log10(12));
    assertEquals(3.0, MathLib::log10(MathLib::pow(10,3)));

    // x * pow(2,exponent)
    assertEquals(MathLib::pow(2,4), MathLib::ldexp(2,3));
    assertEquals(80.0, MathLib::ldexp(10,3));

    assertEquals(MathLib::pow(2,4), MathLib::ldexp(2,3));
    assertEquals(80.0, MathLib::ldexp(10,3));

    // x = significand * 2 ^ exponent
    // 80 = 0.625 * 2 ^ 7
    int exp = 0;
    assertEquals(0.625, MathLib::frexp(80.0, &exp));
    assertEquals(7, exp);

    //modf(12.23, &a) = 0.23 and a = 12.0
    double intPart = 0;
    assertEquals(0.23, MathLib::modf(12.23, &intPart));
    assertEquals(12.0, intPart);

}

void Test::test_MathLib_hyperbolic()
{
    setUpErrorMessage("test_MathLib_hyperbolic() - failed");

    assertEquals((MathLib::exp(3) + MathLib::exp(-3))/2, MathLib::cosh(3));
    assertEquals((MathLib::exp(3) - MathLib::exp(-3))/2, MathLib::sinh(3));
    assertEquals((MathLib::exp(3) - MathLib::exp(-3))/(MathLib::exp(3) + MathLib::exp(-3)), MathLib::tanh(3));

    assertEquals(MathLib::log(33 + MathLib::sqrt(33*33 - 1)), MathLib::acosh(33));
    assertEquals(MathLib::log(33 + MathLib::sqrt(33*33 + 1)), MathLib::asinh(33));

    //ERREUR NEED TO SEE WHATS GOING ON THERE
    //assertEquals(MathLib::log(0.5*MathLib::log((double)(1.0+0.6)/(1.0-0.6))), MathLib::atanh(0.6));

}

void Test::test_power()
{
    setUpErrorMessage("test_power() - failed");

    assertEquals(8.0, MathLib::pow(2, 3));
    assertEquals(0.001, MathLib::pow(0.1, 3));
    assertEquals(10000.0, MathLib::pow(10, 4));

    assertEquals(25.0, MathLib::sqrt(625));
    assertEquals(11.0, MathLib::sqrt(121));
    assertEquals(3.0, MathLib::sqrt(9));
    assertEquals(11.09053, MathLib::sqrt(123));

    //hypotenuse of the right triangle
    assertEquals(5.0, MathLib::hypot(3,4));
    assertEquals(6.40312, MathLib::hypot(4,5));

    assertEquals(2.0, MathLib::cbrt(8.0));
    assertEquals(5.0, MathLib::cbrt(125.0));
}

void Test::test_nearest_absolute_remainder()
{
    setUpErrorMessage("test_nearest_absolute_remainder() - failed");

    //next nearest integer
    assertEquals(4.0, MathLib::ceil(pi));
    assertEquals(3.0, MathLib::ceil(2.987));

    assertEquals(3.0, MathLib::fabs(-3.0));
    assertEquals(3.0, MathLib::fabs(3.0));

    //previous nearest integer
    assertEquals(3.0, MathLib::floor(pi));
    assertEquals(2.0, MathLib::floor(2.987));

    assertEquals(36.0, fmod(4587, 123));
}

void Test::test_miscellaneous()
{
    setUpErrorMessage("test_miscellaneous() - failed");

    assertEquals(0, MathLib::isinf(NAN));
    assertEquals(0, MathLib::isinf(10));
    assertEquals(1, MathLib::isinf(INFINITY));
    assertEquals(1, MathLib::isinf(-INFINITY));
    assertTrue(MathLib::finite(33) != 0);
    assertEquals(0, MathLib::finite(NAN));

    // x 2^n = scalbn(x,n)
    assertEquals(MathLib::pow(2,4), MathLib::scalbn(2,3));
    assertEquals(80.0, MathLib::scalbn(10,3));

    assertEquals(MathLib::pow(2,4), MathLib::scalb(2,3));
    assertEquals(80.0, MathLib::scalb(10,3));

    assertEquals(MathLib::fmod(4587, 123), MathLib::drem(4587, 123));
    assertEquals(MathLib::fmod(45824, 1231), MathLib::drem(45824, 1231));
    assertEquals(MathLib::fmod(10, 1), MathLib::drem(10, 1));

    //x copies the sign of y
    assertEquals(33.0, MathLib::copysign(33, 44));
    assertEquals(-33.0, MathLib::copysign(33, -44));
    assertEquals(33.0, MathLib::copysign(-33, 44));
    assertEquals(-33.0, MathLib::copysign(-33, -44));

    assertTrue(MathLib::isnan(NAN) != 0);
    assertTrue(MathLib::isnan(1) == 0);
    assertTrue(MathLib::isnan(INFINITY_POSITIVE) == 0);

    assertEquals(MathLib::ceil(MathLib::logb(MathLib::fabs(75485))), (double)MathLib::ilogb(75485));
    assertEquals(12.0, MathLib::rint(12.2));
    assertEquals(12.0, MathLib::rint(12.49));
    assertEquals(12.0, MathLib::rint(12.5));
    assertEquals(13.0, MathLib::rint(12.51));
    assertEquals(13.0, MathLib::rint(13.0));

    assertEquals(12.21, MathLib::nextafter(12.21, 13.0));
    assertEquals(12.21, MathLib::nextafter(12.21, -13.0));

    assertEquals(MathLib::fmod(4587, 123), MathLib::remainder(4587, 123));
    assertEquals(MathLib::fmod(45824, 1231), MathLib::remainder(45824, 1231));
    assertEquals(MathLib::fmod(10, 1), MathLib::remainder(10, 1));

    assertEquals(12.0, MathLib::round(12.2));
    assertEquals(12.0, MathLib::round(12.49));
    assertEquals(13.0, MathLib::round(12.5));
    assertEquals(13.0, MathLib::round(12.51));
    assertEquals(13.0, MathLib::round(13.0));

    assertEquals(12.0, MathLib::trunc(12.2));
    assertEquals(12.0, MathLib::trunc(12.49));
    assertEquals(12.0, MathLib::trunc(12.5));
    assertEquals(12.0, MathLib::trunc(12.51));
    assertEquals(13.0, MathLib::trunc(13.0));
}

void Test::test_Util()
{
    setUpErrorMessage("test_Util() - failed");

    long long tmp = Util::getEffectiveTime();
    Util::sleep(1000);
    assertEquals(tmp + 1, Util::getEffectiveTime());

    assertEquals(0.0, Util::diff180(360.0, 360.0));
    //360=0 -> 170, diff = 170
    assertEquals(170.0, Util::diff180(170.0, 360.0));
    assertEquals(0.0, Util::diff180(0.0, 360.0));
    assertEquals(0.0, Util::diff180(-180.0, 180.0));
    //40 -> 90, diff = -50
    assertEquals(-50.0, Util::diff180(40.0, 90.0));
    //-20 -> 80 = -100
    assertEquals(-100.0, Util::diff180(-20.0, 80.0));

    StarData starData1;
    StarData starData2;

    starData1.az = 1;
    starData1.el = 2;
    starData1.ra = 3;
    starData1.dec = 4;
    starData1.time = 5;

    starData2.az = 1;
    starData2.el = 2;
    starData2.ra = 3;
    starData2.dec = 4;
    starData2.time = 5;

    assertTrue(!Util::goodAlignmentGeometry(starData1, starData2));

    starData1.az = 1;
    starData1.el = 2;
    starData1.ra = 3;
    starData1.dec = 4;
    starData1.time = 5;

    starData2.az = 1;
    starData2.el = 50;
    starData2.ra = 3;
    starData2.dec = 4;
    starData2.time = 5;

    assertTrue(!Util::goodAlignmentGeometry(starData1, starData2));


    starData1.az = 1;
    starData1.el = 2;
    starData1.ra = 3;
    starData1.dec = 4;
    starData1.time = 5;

    starData2.az = 100;
    starData2.el = 50;
    starData2.ra = 3;
    starData2.dec = 4;
    starData2.time = 5;

    assertTrue(Util::goodAlignmentGeometry(starData1, starData2));
}

void Test::test_Encoder()
{
    setUpErrorMessage("test_Encoder() - failed");

    Encoder encoder(23, 24);
    assertEquals(23, encoder.pin_a);
    assertEquals(24, encoder.pin_b);

    assertEquals(1, Encoder::_encoders_ptr.size());

    Encoder encoder2(21, 22);
    assertEquals(21, encoder2.pin_a);
    assertEquals(22, encoder2.pin_b);

    assertEquals(2, Encoder::_encoders_ptr.size());

    encoderNameSpace::_callback();
}

void Test::test_Data()
{
    setUpErrorMessage("test_Data() - failed");

    StarData starData1;
    StarData starData2;

    starData1.az = 1;
    starData1.el = 2;
    starData1.ra = 3;
    starData1.dec = 4;
    starData1.time = 5;

    starData2.az = 10;
    starData2.el = 3.;
    starData2.ra = 30;
    starData2.dec = 40;
    starData2.time = 5;

    Data data(starData1, starData2);

    data.setEncoderReadRate(100000); //100 Khz
    data.setEncoderResolution(10000, 10000);

    //Set by user.
    //Look up in the dico to find RA and DEC of the target
    data.setTarget(50, 60);
    data.setStarName("target star name");

    data.applyAlignmentData();

    data.updateCurrentAzEl(2000, 3000);
    data.calculateTargetAzEl();

    std::cout << "is aligned " << data.isAligned() << std::endl;
    std::cout << "target AZ = " << data.getTargetAz() << std::endl;
    std::cout << "target EL = " << data.getTargetEl() << std::endl;

}


void Test::test_Object()
{
    setUpErrorMessage("test_Object() - failed");

    Object object("dsfds", 22, 22, "dsq");

    Object::fill();
    assertEquals(485, Object::_objects_ptr.size());
    assertEquals(485, Object::_objects_ptr.size());
}
