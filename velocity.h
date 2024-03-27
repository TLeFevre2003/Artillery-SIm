/***********************************************************************
 * Header File:
 *    VELOCITY
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about speed
 * 
 * ticket 1: 21 minutes
 * ticket 2: 6 minutes
 * ticket 3: 30 minuites
 * ticket 4: 5 minuites
 * ticket 5: 0 minuites
 * ticket 6: 0 minuites
 ************************************************************************/

#pragma once
#include "acceleration.h"

class Angle;
class Acceleration;
class TestVelocity;
class TestProjectile;

 /*********************************************
  * Velocity
  * I feel the need, the need for speed
  *********************************************/
class Velocity
{
   friend TestProjectile;
   friend TestVelocity;
public:
   // constructors
   Velocity()                     : dx(0.0), dy(0.0) { }
   Velocity(double dx, double dy) : dx(dx), dy(dy) { }

   // getters
   double getDX()       const { return dx; }
   double getDY()       const { return dy; }
   double getSpeed()    const;

   // setters
   void setDX(double dx) { this->dx = dx; }
   void setDY(double dy) { this->dy = dy; }
   void set(const Angle & angle, double magnitude);
   void addDX(double dx) { this->dx += dx; }
   void addDY(double dy) { this->dy += dy; }
   void add(Acceleration acceleration, double time);
   Velocity& operator + (const Velocity& rhs)
   {
      this->addDX(rhs.dx);
      this->addDY(rhs.dy);
      return *this;
   }

   // this function will reverse the angle of the velosity but keep the magnitude
   void reverse() {dx *= -1.0; dy *= -1.0; }

private:
   double dx;           // horizontal velocity
   double dy;           // vertical velocity
};

