/***********************************************************************
 * Header File:
 *    ACCELERATION
 * Author:
 *    Br. Helfrich, Tyler LeFevre and Jason Chandler
 * Summary:
 *    Everything we need to know about acceleration
 ************************************************************************/
// ticket 3 10 minutes
// ticket 4 3 minutes

#pragma once

class Angle;
class TestAcceleration;
class TestVelocity;

/*********************************************
 * Acceleration
 * Includes all we need for acceleration.
 *********************************************/
class Acceleration
{
   friend TestAcceleration;
   friend TestVelocity;
private:
   //attributes
   double ddx;     // horizontal acceleration
   double ddy;     // vertical acceleration
public:
   // constructors
   Acceleration()                       : ddx(0), ddy(0)     { }
   Acceleration(double ddx, double ddy) : ddx(ddx), ddy(ddy) { }

   // getters
   double getDDX()   const           {return ddx;}
   double getDDY()   const           {return ddy;}
                                     
   // setters
   void setDDX(double ddx)           {this->ddx = ddx;}
   void setDDY(double ddy)           {this->ddy = ddy;}
   void set(const Angle & a, double magnitude);
   
   // adders
   void addDDX(double ddx){ this->ddx += ddx;}
   void addDDY(double ddy){ this->ddy += ddy;}
   void add   (const Acceleration& rhs);
};


