#include <stdbool.h>
#include "StarData.h"
#include <string>

#ifndef TEST_CASE_H
#define TEST_CASE_H


class TestCase
{
public:

    void assertNan(int i);
    void assertNan(double d);

    void assertTrue(bool condition);

    void assertEquals(int expected, int actual);
    void assertEquals(std::string expected, std::string actual);
    void assertEquals(double expected, double actual);

    void assertGreater(double expected, double actual);
    void assertGreater(int expected, int actual);

    void assertLess(double expected, double actual);
    void assertLess(int expected, int actual);

    void fail();

protected:
    void setUpErrorMessage(std::string exception_error_msg);

private:

    std::string toString(double d);
    std::string toString(int i);

    std::string exception_error_msg;

};

#endif //TEST_CASE_H
