#pragma once
#include "position.h"
#include <cmath>
#include <iostream>
#include <cassert>

/*****************************
*PROTOTYPE
* authors: Jason Chandler, Tyler Lefevre
* This is a class we made to give oursselves a clean workingspace to complete lab 7.
*****************************/
class Prototype
{
private:
   Position postion;
   const double PI = 3.14159265389;
   double angle;
   double DX;
   double DY;
   double gravity;
   double coeffiecent;
   double airDensity;
   double surfaceArea;
   const double mass = 46.7;

public:
   Prototype(double angle) 
   {
      this->angle = convertDegToRad(angle);
      DX = 0;
      DY = 0;
      gravity = 9.8;
      coeffiecent = 0.3;
      airDensity = 0.6;
      surfaceArea = PI * 0.25 * (0.15489) * (0.15489);
   }

   double computeDistance(double s, double v, double a, double t)
   {
      return s + (v * t) + (0.5 * a * t * t);
   }

   double computeAcceleration(double f, double m)
   {
      return (f / m);
   }

   double computeVelocity(double v, double a, double t)
   {
      return v + (a * t);
   }

   double computeVerticalComponent(double a, double total)
   {
      return total * cos(a);
   }

   double computeHorizontalComponent(double a, double total)
   {
      return total * sin(a);
   }

   double computeTotalComponent(double x, double y)
   {
      return sqrt(x * x + y * y);
   }

   double convertDegToRad(double d)
   {
      return (d * 2 * PI / 360.0);
   }
   void computeAngleFromComponents()
   {
      angle = atan2(DX, DY);
   }

   double computeDrag()
   {
      return 0.5 * coeffiecent * airDensity * computeTotalComponent(DX,DY) * computeTotalComponent(DX, DY) * surfaceArea;
   }

   double linearI(double x, double xf,double x0, double yf, double y0)
   {
      return y0 + ((x - x0) * (yf - y0) / (xf - x0));
   }

   void computeGravity()
   {
      double altitude = postion.getMetersY();
      double G0;
      double G1;
      double A0;
      double A1;

      assert(altitude >= 0);
      if (0.0 <= altitude < 1000.0)
      {
         G0 = 9.807;
         G1 = 9.804;
         A0 = 0.0;
         A1 = 1000;
      }
      else if (1000.0 <= altitude < 2000.0)
      {
         G0 = 9.804;
         G1 = 9.801;
         A0 = 1000;
         A1 = 2000;
      }
      else if (2000.0 <= altitude < 3000.0)
      {
         G0 = 9.801;
         G1 = 9.797;
         A0 = 2000;
         A1 = 3000;
      }
      else if (3000.0 <= altitude < 4000.0)
      {
         G0 = 9.797;
         G1 = 9.794;
         A0 = 3000;
         A1 = 4000;
      }
      else if (4000.0 <= altitude < 5000.0)
      {
         G0 = 9.794;
         G1 = 9.791;
         A0 = 4000;
         A1 = 5000;
      }
      else if (5000.0 <= altitude < 6000.0)
      {
         G0 = 9.791;
         G1 = 9.788;
         A0 = 5000;
         A1 = 6000;
      }
      else if (6000.0 <= altitude < 7000.0)
      {
         G0 = 9.788;
         G1 = 9.785;
         A0 = 6000;
         A1 = 7000;
      }
      else if (7000.0 <= altitude < 8000.0)
      {
         G0 = 9.785;
         G1 = 9.782;
         A0 = 7000;
         A1 = 8000;
      }
      else if (8000.0 <= altitude < 9000.0)
      {
         G0 = 9.782;
         G1 = 9.779;
         A0 = 8000;
         A1 = 9000;
      }
      else if (9000.0 <= altitude < 10000.0)
      {
         G0 = 9.779;
         G1 = 9.776;
         A0 = 9000;
         A1 = 10000;
      }
      else if (10000.0 <= altitude < 15000.0)
      {
         G0 = 9.776;
         G1 = 9.761;
         A0 = 10000;
         A1 = 15000;
      }
      else if (15000.0 <= altitude < 20000.0)
      {
         G0 = 9.761;
         G1 = 9.745;
         A0 = 15000;
         A1 = 20000;
      }
      else if (20000.0 <= altitude)
      {
         G0 = 9.745;
         G1 = 9.730;
         A0 = 20000;
         A1 = 25000;
      }

      gravity = linearI(altitude, A1, A0, G1, G0) * -1;
   }
   
   void simulate(double timePerIncrement, double muzzleVelocity)
   {
      double hangTime = 0.0;
      DX = computeHorizontalComponent(this->angle, muzzleVelocity);
      DY = computeVerticalComponent(this->angle, muzzleVelocity);
      double DDX = 0;
      double DDY = 0;
      gravity = -9.8;
      while (postion.getMetersY() >= 0)
      {
         computeGravity();
         computeAngleFromComponents();

         double dragAcceleration = computeDrag() / mass;
         double horizontalDrag = computeHorizontalComponent(angle, dragAcceleration);
         double verticalDrag = computeVerticalComponent(angle, dragAcceleration);
         DDX = -1 * horizontalDrag;
         DDY = gravity - verticalDrag;

         DX = computeVelocity(DX, DDX, timePerIncrement);
         DY = computeVelocity(DY, DDY, timePerIncrement);

         postion.setMetersX(computeDistance(postion.getMetersX(), DX, DDX, timePerIncrement));
         postion.setMetersY(computeDistance(postion.getMetersY(), DY, DDY, timePerIncrement));

         hangTime += timePerIncrement;
      }
      
      std::cout << "Distance:" << postion.getMetersX() << " Altitude" << postion.getMetersY() << " Hang Time: " << hangTime << std::endl;
   }
};

