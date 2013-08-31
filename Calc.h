#ifndef CALC_H
#define CALC_H

// Sideral rate
#define degreesPerMinute (1.002738 * 0.25)

#define pi 3.14159265358979323846
#define degPerRad (360.0/(2*pi))
#define radPerDeg (1.0/degPerRad)
#define radPerMinute (degreesPerMinute*radPerDeg)

#include <stdbool.h>
#include <string>

class Calc
{
public:
    // A utility function.  Has no affect on main conversion routines.
    // Works equally well for any polar coordinate system: altaz or
    // equatorial. Values in radians!
    double calcSeparation(double az1, double el1, double az2, double el2);

    // Same as above, but values in degrees.
    double calcDegSeparation(double az1, double el1, double az2, double el2);

    // All angles in degrees, time in seconds.
    void setAlignmentData(int i, double ra, double dec, double az, double el, double time);


    // Optional if z1, z2, and z3 are all zero.
    void setZ123(double z1, double z2, double z3);

    double getZ3(void);

    // Call after calling setAlignmentData twice.
    bool finalizeAlignment(bool optimize_z3);

    //       CONVERT EQUATORIAL --> TELESCOPE
    // All angles in degrees, time in seconds.
    void EqToAzEl(double ra, double dec, double time,bool flipped, double *azptr, double *elptr);

    //      CONVERT TELESCOPE --> EQUATORIAL
    // All angles in degrees, time in seconds.
    void AzElToEq(double az, double el, double time, double *raptr, double *decptr);

    Calc()
    {
        Z1 = 0;  // All in radians
        Z2 = 0;
        Z3 = 0;
    }


private:

    ///PRIVATE FUNCTIONS///

    static double sqr(double x);

    void printDebugMsg(std::string msg);

    void printNumericDebugMsg(std::string str, double val);

    //        DETERMINANT SUBROUTINE
    // Scalar variable W gets set from array VV.
    // This is the only place VV is read.
    // Originally "GOSUB 650"
    void VVtoW(void);

    //        ANGLE SUBROUTINE
    // Sets scalar variables F and H (usually Az and El) from column 1 of array YY.
    // This is essentially a rectangular-polar conversion, the inverse of
    // AzEltoYY0() (Except that the Z123 corrections are not done).
    // All data will be in radians.
    // H will be normalized to a 0 .. 2*pi range.
    // Originally "GOSUB 685"

    void YY1toFH(bool flipped);

    //           SUBROUTINE
    // Sets column 0 of array YY based on scalar variables
    // F and H (Az and El), Z1, Z2, and Z3.
    // It does a polar-rectangular conversion, and applies
    // the Z123 factors to convert from apparent to true
    // telescope angles.
    // Has Taki's 2002 bug fix.
    // Originally "GOSUB 750"
    void AzEltoYY0(void);

    //           SUBROUTINE
    // Sets column 1 of array YY based on scalar variables F and H (Az and El),
    // Z1, and Z2.
    // It is used for applying the reverse Z123 correction,
    // to go from true to apparent telescope angles.
    // Originally "GOSUB 785"
    // Has Taki's bug fix.
    void AzElToYY1(void);

    // This converts the true az/el (in F and H) to the
    // apparent telescope az/el (i.e. it applies the
    // inverse Z123 correction).
    void TrueToApparentAzEl(bool flipped);

    // This converts the apparent az/el (in F and H) to the
    // true telescope az/el (i.e. it applies the Z123 correction).
    // Function AzEltoYY0() does all the real work.
    // NOTE: This trashes array YY, so be careful where
    // you use it.
    void ApparentToTrueAzEl(void);

    // Calculate the apparent angular separation of the two stars,
    // (as stored in alignAz[] and alignEl[]), and corrected
    // by the current values of Z1, Z2, and Z3.

    double calcApparentSeparation(void);

    bool optimizeZ3(void);

    ///VARIABLES///

    double QQ[4][4];

    // XX stores the alignment star RA/Dec data, in rectangular form.
    //   Note: Column 0 of XX is never used.
    // VV serves as the input to the determinant function VVtoW().
    // YY (especially column 0) is really a temporarily holding area.
    // QQ and RR hold the critical transformation data.

    double VV[4][4],RR[4][4],XX[4][4],YY[4][4];


    double F, H, W;

    // Alignment data (in radians) as given by setAlignmentData(),
    // except that az is reversed, like the algorithms expect it.
    // As we iterate to optimize the value Z3, we will re-initialize
    // columns 1 and 2 of YY with the corrected az/el data.
    double alignAz[3];
    double alignEl[3];
    double alignRA[3];
    double alignDec[3];


    //      MOUNT ERROR, IF ANY
    double Z1;  // All in radians
    double Z2;
    double Z3;

};

#endif //CALC_H
