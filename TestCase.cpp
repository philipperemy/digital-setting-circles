#include "TestCase.h"
#include "TestException.h"
#include <cmath>
#include <sstream>

void TestCase::setUpErrorMessage(std::string exception_error_msg)
{
    this->exception_error_msg = exception_error_msg;
}

void TestCase::assertNan(double d)
{
    if(fabs(static_cast<double>(d) - d) > 0.00001)
    {
        setUpErrorMessage(exception_error_msg + ": NAN = " + toString(d));
        fail();
    }
}

void TestCase::assertNan(int i)
{
    if(static_cast<int>(i) != i)
    {
        setUpErrorMessage(exception_error_msg + ": NAN = " + toString(i));
        fail();
    }
}

void TestCase::assertTrue(bool condition)
{
    if(!condition)
    {
        fail();
    }
}

void TestCase::assertEquals(std::string expected, std::string actual)
{
    if(expected.compare(actual) != 0)
    {
        setUpErrorMessage(exception_error_msg + ": expected = " + expected + ", actual = " + actual);
        fail();
    }
}

void TestCase::assertEquals(double expected, double actual)
{
    if(fabs(expected - actual) > 0.00001)
    {
        setUpErrorMessage(exception_error_msg + ": expected = " + toString(expected) + ", actual = " + toString(actual));
        fail();
    }
}

void TestCase::assertEquals(int expected, int actual)
{
    if(expected != actual)
    {
        setUpErrorMessage(exception_error_msg + ": expected = " + toString(expected) + ", actual = " + toString(actual));
        fail();
    }
}

void TestCase::fail()
{
    throw TestException(this->exception_error_msg);
}

std::string TestCase::toString(double d)
{
    std::stringstream s;
    s << d;
    return s.str();
}

std::string TestCase::toString(int i)
{
    std::stringstream s;
    s << i;
    return s.str();
}

void TestCase::assertGreater(double min_value, double actual)
{
    if(actual < min_value)
    {
        setUpErrorMessage(exception_error_msg + ": min_value = " + toString(min_value) + ", actual = " + toString(actual));
        fail();
    }
}

void TestCase::assertGreater(int min_value, int actual)
{
    if(actual < min_value)
    {
        setUpErrorMessage(exception_error_msg + ": min_value = " + toString(min_value) + ", actual = " + toString(actual));
        fail();
    }
}

void TestCase::assertLess(double max_value, double actual)
{
    if(actual > max_value)
    {
        setUpErrorMessage(exception_error_msg + ": max_value = " + toString(max_value) + ", actual = " + toString(actual));
        fail();
    }
}

void TestCase::assertLess(int max_value, int actual)
{
    if(actual > max_value)
    {
        setUpErrorMessage(exception_error_msg + ": max_value = " + toString(max_value) + ", actual = " + toString(actual));
        fail();
    }
}
