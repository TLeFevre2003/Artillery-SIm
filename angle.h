/***********************************************************************
 * Header File:
 *    ANGLE
 * Author:
 *    Br. Helfrich, Tyler LeFevre and Jason Chandler
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>   // for M_PI which is 3.14159
#include "testAngle.h"

 /************************************
  * ANGLE
  ************************************/
class Angle
{
   friend TestAngle;
private:
   //atributes:
   double radians;   // 360 degrees equals 2 PI radians

   double normalize(double radians) const;

   // Converters
   double convertToDegrees(double radian)  const { return (360.0 * radians) / (2.0 * M_PI); }
   double convertToRadians(double degrees) const { return normalize((degrees * 2.0 * M_PI) / 360.0); }
public:
   // Constructors
   Angle()                 : radians(0)                          {}
   Angle(const Angle& rhs) : radians(rhs.radians)                {}
   Angle(double degrees)   : radians(convertToRadians(degrees))  {}

   // Getters
   double getDegrees() const { return convertToDegrees(this->radians);}
   double getRadians() const { return radians;                        }

   // Setters
   void setDegrees(double degrees) { radians = convertToRadians(degrees);}
   void setRadians(double radians) { this->radians = normalize(radians); }
   void setUp()                    {radians        = 0;                  }
   void setDown()                  {radians        = M_PI;               }
   void setRight()                 {radians        = M_PI_2;             } // M_2_PI == PI / 2}
   void setLeft()                  {radians        = M_PI + M_PI_2;      }
   void reverse()                  {radians       += M_PI;               }
   
   // Adder
   Angle& add(double delta) { radians = normalize(radians + delta); return *this;}
};

