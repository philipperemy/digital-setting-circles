#include "MathLib.h"
#include "Calc.h"

#include <iostream>

double Calc::sqr(double x)
{
  return x*x;
}

void Calc::printDebugMsg(std::string msg)
{
    std::cerr << msg << std::endl;
}


void printNumericDebugMsg(std::string str, double val)
{
    std::cerr << str << " " << val << std::endl;
}


void Calc::VVtoW(void)
{
 W = VV[1][1]*VV[2][2]*VV[3][3]+VV[1][2]*VV[2][3]*VV[3][1];
 W = W+VV[1][3]*VV[3][2]*VV[2][1];
 W = W-VV[1][3]*VV[2][2]*VV[3][1]-VV[1][1]*VV[3][2]*VV[2][3];
 W = W-VV[1][2]*VV[2][1]*VV[3][3];
}


void Calc::YY1toFH(bool flipped)
{
  double C = MathLib::sqrt(sqr(YY[1][1])+sqr(YY[2][1]));

  // Since C is always non-negative, H will be between -90 and 90 degrees.
  if (C==0 && YY[3][1]==0)
    H = 0;  // Undefined result!
  else
    H = MathLib::atan2(YY[3][1], C);

  if (C==0)
    F = 1; // Elevation is +-90 deg, so az is arbitrary.
  else {
    // Note: Since C>0, both YY[2][1] and YY[1][1] must be != 0.
    F = MathLib::atan2(YY[2][1], YY[1][1]);
    // The atan2() function provides a 4-quadrant result, but in
    // the -p...pi range instead of 0...2*pi.
    if (F<0)
      F += (2*pi);
  }

  // No longer any need to clip F to 0..2*pi.

  // If desired, convert the result to flipped mode.
  if (flipped) {
    // Flip the elevation to the other side of the zenith.
    if (H >= 0)
      H = pi - H;
    else
      H = -pi - H;

    // Rotate (not flip) the azimuth 180 degrees.
    F -= pi;
    if (F<0)
      F += (2*pi);
  }
}


void Calc::AzEltoYY0(void)
{
  H += Z3;
  YY[1][0] = MathLib::cos(F)*MathLib::cos(H) - MathLib::sin(F)*Z2 + MathLib::sin(F)*MathLib::sin(H)*Z1;
  YY[2][0] = MathLib::sin(F)*MathLib::cos(H) + MathLib::cos(F)*Z2 - MathLib::cos(F)*MathLib::sin(H)*Z1;
  YY[3][0] = MathLib::sin(H);
}


void Calc::AzElToYY1(void)
{
  YY[1][1] = MathLib::cos(F)*MathLib::cos(H) + MathLib::sin(F)*Z2 - MathLib::sin(F)*MathLib::sin(H)*Z1;
  YY[2][1] = MathLib::sin(F)*MathLib::cos(H) - MathLib::cos(F)*Z2 + MathLib::cos(F)*MathLib::sin(H)*Z1;
  YY[3][1] = MathLib::sin(H);
}


void Calc::TrueToApparentAzEl(bool flipped)
{
  AzElToYY1();
  YY1toFH(flipped);
  H -= Z3;
}


void Calc::ApparentToTrueAzEl(void)
{
  int J;

  AzEltoYY0();
  for (J=1; J<=3; J++)
    YY[J][1] = YY[J][0];
  YY1toFH(false);
}


double Calc::calcApparentSeparation(void)
{
  double corrAz1, corrAz2, corrEl1, corrEl2;

  F = alignAz[1];
  H = alignEl[1];
  ApparentToTrueAzEl();
  corrAz1 = F;
  corrEl1 = H;

  F = alignAz[2];
  H = alignEl[2];
  ApparentToTrueAzEl();
  corrAz2 = F;
  corrEl2 = H;

  return calcSeparation(corrAz1, corrEl1, corrAz2, corrEl2);
}


bool Calc::optimizeZ3(void)
{

  double maxGuess;
  double upperGuess, lowerGuess;
  double upperError, lowerError;

  // Our residual error threshold
  const double maxErr = 0.01*radPerDeg;

  int ntries;

  // Calculate the true angular separation of the two stars,
  // based on their RA/Dec.  This need be calculated only once.
  const double trueSep =
	calcSeparation(alignRA[1], alignDec[1], alignRA[2], alignDec[2]);

  if (!MathLib::finite(trueSep)) {
    printDebugMsg("Can't calculate star separation!");
    return false;
  }

  if (trueSep < 5.0*radPerDeg) {
    printDebugMsg("Stars too close together!");
    return false;
  }

  maxGuess = 10.0*radPerDeg;
  if (maxGuess > trueSep/2)
    maxGuess = trueSep/2;


  Z3 = upperGuess = maxGuess;
  upperError = calcApparentSeparation() - trueSep;
  if (MathLib::fabs(upperError) <= maxErr) {
    printDebugMsg("Lucky pos. first guess");
    return true;  // Lucky guess!
  }

  Z3 = lowerGuess = -maxGuess;
  lowerError = calcApparentSeparation() - trueSep;
  if (MathLib::fabs(lowerError) <= maxErr) {
    printDebugMsg("Lucky neg. first guess");
    return true;  // Lucky guess!
  }

  // For the interpolation to succeed, the upper and
  // lower errors must be of opposite sign.
  if (upperError * lowerError > 0.0) {
    printDebugMsg("Correct Z3 out of range");
    return false;
  }

  ntries = 0;
  for (;;) {
    double newGuess, newError;
    ntries++;

    // Interpolate between the upper and lower guesses to
    // get a new guess.

    Z3 = newGuess = lowerGuess +
	((lowerError/(lowerError-upperError))*(upperGuess-lowerGuess));

    newError = calcApparentSeparation() - trueSep;

    if (MathLib::fabs(newError) <= maxErr) {
        std::cout << "Converged after " << ntries << " tries: Z3= " << Z3*degPerRad << std::endl;
      return true;  // We have converged!  Z3 is set.
    }

    if (ntries > 25) {
      printDebugMsg("No convergence after 25 tries");
      return false;  // Failure to converge
    }

    // NewGuess replaces either lowerGuess or upperGuess, depending
    // on the sign of the newError.

    if (lowerError * newError > 0) {
      // newError has the same sign as lowerError
      lowerGuess = newGuess;
      lowerError = newError;
    } else {
      upperGuess = newGuess;
      upperError = newError;
    }
  }

  // We should never get here!
  printDebugMsg("Broke out of loop!?!");

  return false;
}


/////////////////////////////////////////////////////////////////
// Externally callable functions  ///////////////////////////////
/////////////////////////////////////////////////////////////////


// A utility function.  Has no affect on main conversion routines.
// Works equally well for any polar coordinate system: altaz or
// equatorial.
double Calc::calcSeparation(double az1, double el1, double az2, double el2)
{
  double cossep;

  cossep = (MathLib::sin(el1)*MathLib::sin(el2)) + (MathLib::cos(el1)*MathLib::cos(el2)*MathLib::cos(az1-az2));

  // Avoid a domain error for acos due to rounding.
  if (cossep >= 1.0)
    return 0.0;
  if (cossep <= -1.0)
    return pi;

  return MathLib::acos(cossep);
}


// Same as above, but values in degrees.
double Calc::calcDegSeparation(double az1, double el1, double az2, double el2)
{
  return calcSeparation(az1*radPerDeg, el1*radPerDeg,
			az2*radPerDeg, el2*radPerDeg);
}


// No longer necessary to call this before setAlignmentData().
void Calc::setZ123(double z1, double z2, double z3)
{
  // All are converted to radians.
  Z1 = z1 * radPerDeg;
  Z2 = z2 * radPerDeg;
  Z3 = z3 * radPerDeg;
}


double Calc::getZ3(void)
{
  return Z3*degPerRad;
}


// Angles in degrees, time in seconds.
void Calc::setAlignmentData(int i, double ra, double dec,
		      double az, double el, double time)
{

  if (i<0 || i>1)
    return;

  i++;  // I must be 1 or 2 to index the arrays!

  // This entire package measures azimuth backwards!
  alignAz[i] = (360.0-az)*radPerDeg;
  alignEl[i] = el*radPerDeg;
  alignRA[i] =  (ra-degreesPerMinute*time)/degPerRad;
  alignDec[i] =  dec/degPerRad;
}


// Call after calling setAlignmentData twice.
bool Calc::finalizeAlignment(bool optimize_z3)
{
  int I, J, L, M, N;
  double A;
  double E;
  bool status;

  if (optimize_z3) {
    Z3 = 0.0;   // If optimization fails, leave Z3 set to 0.0
    status = optimizeZ3();
  } else
    status = true;

  // Keep going even if the Z3 optimization fails.

  // Initialize columns 1 and 2 of YY with the alignment az/el data,
  // corrected with Z123.

  F = alignAz[1];
  H = alignEl[1];
  AzEltoYY0();
  YY[1][1] = YY[1][0]; YY[2][1] = YY[2][0]; YY[3][1] = YY[3][0];

  F = alignAz[2];
  H = alignEl[2];
  AzEltoYY0();
  YY[1][2] = YY[1][0]; YY[2][2] = YY[2][0]; YY[3][2] = YY[3][0];

  // Set third column of array YY.
  YY[1][3]=YY[2][1]*YY[3][2]-YY[3][1]*YY[2][2];
  YY[2][3]=YY[3][1]*YY[1][2]-YY[1][1]*YY[3][2];
  YY[3][3]=YY[1][1]*YY[2][2]-YY[2][1]*YY[1][2];

  // Normalize third column of array YY.
  A=MathLib::sqrt(sqr(YY[1][3])+sqr(YY[2][3])+sqr(YY[3][3]));
  if (A > 0.0) {
    // Avoid 0/0 error if third column is all zeros
    for (I=1; I<=3; I++) {
      YY[I][3] /= A;
    }
  }


  // Initialize columns 1 and 2 of XX with the star RA/Dec data.
  XX[1][1] = MathLib::cos(alignDec[1])*MathLib::cos(alignRA[1]);
  XX[2][1] = MathLib::cos(alignDec[1])*MathLib::sin(alignRA[1]);
  XX[3][1] = MathLib::sin(alignDec[1]);
  XX[1][2] = MathLib::cos(alignDec[2])*MathLib::cos(alignRA[2]);
  XX[2][2] = MathLib::cos(alignDec[2])*MathLib::sin(alignRA[2]);
  XX[3][2] = MathLib::sin(alignDec[2]);

  // Set third column of array XX.
  XX[1][3]=XX[2][1]*XX[3][2]-XX[3][1]*XX[2][2];
  XX[2][3]=XX[3][1]*XX[1][2]-XX[1][1]*XX[3][2];
  XX[3][3]=XX[1][1]*XX[2][2]-XX[2][1]*XX[1][2];

  // Normalize third column of array XX.
  A=MathLib::sqrt(sqr(XX[1][3])+sqr(XX[2][3])+sqr(XX[3][3]));
  if (A > 0.0) {
    // Avoid 0/0 error if third column is all zeros
    for (I=1; I<=3; I++) {
      XX[I][3] /= A;
    }
  }



  //       TRANSFORM MATRIX
  for (I=1; I<=3; I++) {
    for (J=1; J<=3; J++) {
      VV[I][J]=XX[I][J];
    }
  }
  VVtoW(); E=W;

  for (M=1; M<=3; M++) {

    for (I=1; I<=3; I++) {
      for (J=1; J<=3; J++) {
	 VV[I][J]=XX[I][J];
      }
    }

    for (N=1; N<= 3; N++) {
      VV[1][M]=0; VV[2][M]=0; VV[3][M]=0; VV[N][M]=1;
      VVtoW();

      // Avoid problems with divide-by-zero.  Am not sure
      // under what conditions this could actually happen...
      if (W==0 && E==0) {
        QQ[M][N]=1;
      } else if (E==0) {
        QQ[M][N]=1;
        status = false;
      } else {
        QQ[M][N]=W/E;
      }
    }
  }


  for (I=1; I<=3; I++) {
    for (J=1; J<=3; J++) {
       RR[I][J]=0;
    }
  }

  for (I=1; I<=3; I++) {
    for (J=1; J<=3; J++) {
      for (L=1; L<=3; L++) {
	RR[I][J] += (YY[I][L]*QQ[L][J]);
      }
    }
  }

  for (M=1; M<=3; M++) {

     for (I=1; I<=3; I++) {
       for (J=1; J<=3; J++) {
	 VV[I][J]=RR[I][J];
       }
     }

     VVtoW(); E=W;
     for (N=1; N<=3; N++) {
       VV[1][M]=0; VV[2][M]=0; VV[3][M]=0; VV[N][M]=1;
       VVtoW();
       // Avoid problems with divide-by-zero.  Am not sure
       // under what conditions this could actually happen...
       if (W==0 && E==0) {
	 QQ[M][N]=1;
       } else if (E==0) {
	 QQ[M][N]=1;
	 status = false;
       } else {
	 QQ[M][N]=W/E;
       }
     }
  }

  return status;
}


//       CONVERT EQUATORIAL --> TELESCOPE
void Calc::EqToAzEl(double ra, double dec, double time, bool flipped, double *azptr, double *elptr)
{
  int I, J;

  double RA = ra;
  double DEC = dec;

  DEC=DEC/degPerRad;
  RA=(RA-degreesPerMinute*time)/degPerRad;
  XX[1][1]=MathLib::cos(DEC)*MathLib::cos(RA);
  XX[2][1]=MathLib::cos(DEC)*MathLib::sin(RA);
  XX[3][1]=MathLib::sin(DEC);

  YY[1][1]=0; YY[2][1]=0; YY[3][1]=0;
  for (I=1; I<=3; I++) {
    for (J=1; J<=3; J++) {
      YY[I][1] += (RR[I][J]*XX[J][1]);
    }
  }

  YY1toFH(flipped);

  TrueToApparentAzEl(flipped);

  F *= degPerRad;
  H *= degPerRad;

  // This code measures azimuth backwards!
  F = 360.0-F;

  if (azptr)
    *azptr = F;

  if (elptr)
    *elptr = H;
}


//      CONVERT TELESCOPE --> EQUATORIAL
void Calc::AzElToEq(double az, double el, double time, double *raptr, double *decptr)
{
  int I, J;

  F = 360.0 - az; // This code measures azimuth backwards!
  H = el;

  F *= radPerDeg;
  H *= radPerDeg;

  AzEltoYY0();
  XX[1][1]=YY[1][0]; XX[2][1]=YY[2][0]; XX[3][1]=YY[3][0];
  YY[1][1]=0; YY[2][1]=0; YY[3][1]=0;

  for (I=1; I<=3; I++) {
    for (J=1; J<=3; J++) {
      YY[I][1] += (QQ[I][J]*XX[J][1]);
    }
  }
  YY1toFH(false);

  F *= degPerRad;
  H *= degPerRad;

  F += degreesPerMinute*time;

  F=F-MathLib::floor(F/360)*360;
  //F = fmod(F, 360.0);

  if (raptr)
    *raptr = F;

  if (decptr)
    *decptr = H;

}

//     *****************************************
//        FROM SKY & TELESCOPE, FEBRUARY, 1989,
//        PAGES 194-196
//     *****************************************
