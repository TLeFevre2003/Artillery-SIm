/***********************************************************************
 * Source File:
 *    ANGLE
 * Author:
 *    Br. Helfrich, Tyler LeFevre and Jason Chandler
 * Summary:
 *    Everything we need to know about a direction
 *    Source for fmod https://cplusplus.com/reference/cmath/fmod/
 ************************************************************************/

#include "angle.h"
#include <math.h>  // for floor()
#include <cassert>
using namespace std;

 /************************************
  * ANGLE : NORMALIZE
  * Enforce that radian stays in range 0 - 2pi.
  ************************************/
double Angle::normalize(double radians) const
{
   // Use modulus to normalize radians outside of the unit circle.
   radians = fmod (radians, (2 * M_PI));
   
   // If radians is a negative add 2 Pi to it.
   if (radians < 0)
   {
      radians += 2 * M_PI;
   }
   return radians;
}
/*************************************
* ANGLE : getHorizonatal
* return the horitzontal section of the angle
* based on the unit circle
************************************/
double Angle::getHorizontal() const
{
   return 0.0;
}
/*************************************
* ANGLE : getVertical
* return the vertical section of the angle
* based on the unit circle
************************************/
double Angle::getVertical() const
{
   return 0.0;
}

/*************************************
* ANGLE : isRight
* return if the angle is between 0 and pi
************************************/
bool Angle::isRight() const
{
   return false;
}

/*************************************
* ANGLE : isLeft
* return if the angle is between 0 and pi
************************************/
bool Angle::isLeft() const
{
   return false;
}
