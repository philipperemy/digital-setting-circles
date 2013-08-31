#include "MathLib.h"

#include <math.h>
#include <cmath>


double MathLib::acos(double x)
{
    return ::acos(x);
}

double MathLib::asin(double x)
{
    return ::asin(x);
}

double MathLib::atan(double x)
{
    return ::atan(x);
}

double MathLib::atan2(double y, double x)
{
    return ::atan2(y, x);
}

double MathLib::cos(double x)
{
    return ::cos(x);
}

double MathLib::sin(double x)
{
    return ::sin(x);
}

double MathLib::tan(double x)
{
    return ::tan(x);
}

double MathLib::cosh(double x)
{
    return ::cosh(x);
}

double MathLib::sinh(double x)
{
    return ::sinh(x);
}

double MathLib::tanh(double x)
{
    return ::tanh(x);
}

double MathLib::acosh(double x)
{
    return ::acosh(x);
}

double MathLib::asinh(double x)
{
    return ::asinh(x);
}

double MathLib::atanh(double x)
{
    return ::atanh(x);
}

double MathLib::exp(double x)
{
    return ::exp(x);
}

double MathLib::frexp(double x, int *exponent)
{
    return ::frexp(x, exponent);
}

double MathLib::ldexp(double x, int exponent)
{
    return ::ldexp(x, exponent);
}

double MathLib::log(double x)
{
    return ::log(x);
}

double MathLib::log10(double x)
{
    return ::log10(x);
}

double MathLib::modf(double x, double *intpart)
{
    return ::modf(x, intpart);
}

double MathLib::expm1(double x)
{
    return ::expm1(x);
}

double MathLib::log1p(double x)
{
    return ::log1p(x);
}

double MathLib::logb(double x)
{
    return ::logb(x);
}

double MathLib::log2(double x)
{
    return ::log2(x);
}

double MathLib::pow(double x, double y)
{
    return ::pow(x, y);
}

double MathLib::sqrt(double x)
{
    return ::sqrt(x);
}

double MathLib::hypot(double x, double y)
{
    return MathLib::sqrt(x*x+y*y);
}

double MathLib::cbrt(double x)
{
    return ::cbrt(x);
}

double MathLib::ceil(double x)
{
    return ::ceil(x);
}

double MathLib::fabs(double x)
{
    return ::fabs(x);
}

double MathLib::floor(double x)
{
    return ::floor(x);
}

double MathLib::fmod(double x, double y)
{
    return ::fmod(x, y);
}

int MathLib::isinf(double x)
{
    return std::isinf(x);
}

int MathLib::finite(double x)
{
    return ::finite(x);
}

double MathLib::scalbn(double x, int exponent)
{
    return ::scalbn(x, exponent);
}

double MathLib::drem(double x, double y)
{
    return ::fmod(x, y);
}

double MathLib::copysign(double x, double y)
{
    return ::copysign(x, y);
}

int MathLib::isnan(double x)
{
    return std::isnan(x);
}

int MathLib::ilogb(double x)
{
    return ::ilogb(x);
}

double MathLib::rint(double x)
{
    return ::rint(x);
}

double MathLib::nextafter(double x, double y)
{
    return ::nextafter(x, y);
}

double MathLib::remainder(double x, double y)
{
    return ::remainder(x, y);
}

double MathLib::scalb(double x, double exponent)
{
    return ::scalbn(x, exponent);
}

double MathLib::round(double x)
{
    return ::round(x);
}

double MathLib::trunc(double x)
{
    return ::trunc(x);
}
