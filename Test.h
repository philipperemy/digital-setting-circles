#include <stdbool.h>
#include "StarData.h"
#include "TestCase.h"
#include <string>

#ifndef TEST_H
#define TEST_H


class Test : public TestCase
{
public:

    void run_all();

    //StarData.h
    void test_StarData();
    void test_StarDataNamespaceFunctions();

    //MathLib.h
    void test_MathLib_trigonometric();
    void test_MathLib_exponential_logarithmic();
    void test_MathLib_hyperbolic();
    void test_power();
    void test_nearest_absolute_remainder();
    void test_miscellaneous();

    //Util.h
    void test_Util();

    //Encoder.h
    void test_Encoder();

    //Data.h
    void test_Data();

    //Object.h
    void test_Object();
};

#endif //TEST_H
