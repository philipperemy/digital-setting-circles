#ifndef MATHLIB_H
#define MATHLIB_H

class MathLib
{
public:
        /***************************
         * Trigonometric functions *
         ***************************/
        static double acos(double x);				// Arc cosine of x
        static double asin(double x);				// Arc sine of x
        static double atan(double x);				// Arc tangent of x
        static double atan2(double y, double x);	// Arc tangent of y/x
        static double cos(double x);				// Cosine of x
        static double sin(double x);				// Sine of x
        static double tan(double x);				// Tangent of x

        /************************
         * Hyperbolic functions	*
         ************************/
        static double cosh(double x);				// Hyperbolic cosine of x
        static double sinh(double x);				// Hyperbolic sine of x
        static double tanh(double x);				// Hyperbolic tangent of x
        static double acosh(double x);				// Hyperbolic arc cosine of x
        static double asinh(double x);				// Hyperbolic arc sine of x
        static double atanh(double x);				// Hyperbolic arc tangent of x

        /*****************************************
         * Exponential and logarithmic functions *
         *****************************************/
        static double exp(double x);					// Exponential function of x [pow(e,x)]
        static double frexp(double x, int *exponent);	// Break x into normalized fraction and an integral power of 2
        static double ldexp(double x, int exponent);	// x * pow(2,exponent)
        static double log(double x);					// Natural logarithm of x
        static double log10(double x);					// Base 10 logarithm of x
        static double modf(double x, double *intpart);	// Break x into integral and fractional parts
        static double expm1(double x);					// exp(x) - 1
        static double log1p(double x);					// log(1+x)
        static double logb(double x);					// Base 2 signed integral exponent of x
        static double log2(double x);					// Base 2 logarithm of x

        /*******************
         * Power functions *
         *******************/
        static double pow(double x, double y);		// x to the y power [x**y]
        static double sqrt(double x);				// Square root of x [x**0.5]
        static double hypot(double x, double y);	// sqrt(x*x + y*y)	[hypotenuse of right triangle]
        static double cbrt(double x);				// Cube root of x	[x**(1/3)]

        /************************************************************
         * Nearest integer, absolute value, and remainder functions *
         ************************************************************/
        static double ceil(double x);				// Smallest integral value not less than x
        static double fabs(double x);				// Absolute value of x
        static double floor(double x);				// Largest integral value not greater than x
        static double fmod(double x, double y);	// Modulo remainder of x/y

        /***************************
         * Miscellaneous functions *
         ***************************/
        static int    isinf(double x);					// Return 0 if x is finite or NaN, +1 if +Infinity, or -1 if -Infinity
        static int    finite(double x);				// Return nonzero if x is finite and not NaN
        static double scalbn(double x, int exponent);	// x * pow(2,exponent)
        static double drem(double x, double y);		// Remainder of x/y
        static double copysign(double x, double y);	// Return x with its sign changed to match y's
        static int    isnan(double x);					// Return nonzero if x is NaN (Not a Number)
        static int    ilogb(double x);					// Binary exponent of non-zero x
        static double rint(double x);					// Integral value nearest x in direction of prevailing rounding mode
        static double nextafter(double x, double y);	// Next machine double value after x in the direction towards y
        static double remainder(double x, double y);	// Remainder of integer division x/y with infinite precision
        static double scalb(double x, double exponent);// x * pow(2,exponent)
        static double round(double x);					// Round x to nearest integral value away from zero
        static double trunc(double x);					// Round x to nearest integral value not larger than x

private:

};



#endif // MATHLIB_H
