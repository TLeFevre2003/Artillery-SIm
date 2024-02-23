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
   Position position;
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
      double altitude = position.getMetersY();
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
   void computeAirDensity()
   {
       double altitude = position.getMetersY();
       double D0;
       double D1;
       double B0;
       double B1;

       assert(altitude >= 0);

       if (0.0 <= altitude && altitude < 1000.0)
       {
           D0 = 1.225;
           D1 = 1.112;
           B0 = 0.0;
           B1 = 1000.0;
       }
       else if (1000.0 <= altitude && altitude < 2000.0)
       {
           D0 = 1.112;
           D1 = 1.007;
           B0 = 1000.0;
           B1 = 2000.0;
       }
       else if (2000.0 <= altitude && altitude < 3000.0)
       {
           D0 = 1.007;
           D1 = 0.9093;
           B0 = 2000.0;
           B1 = 3000.0;
       }
       else if (3000.0 <= altitude && altitude < 4000.0)
       {
           D0 = 0.9093;
           D1 = 0.8194;
           B0 = 3000.0;
           B1 = 4000.0;
       }
       else if (4000.0 <= altitude && altitude < 5000.0)
       {
           D0 = 0.8194;
           D1 = 0.7364;
           B0 = 4000.0;
           B1 = 5000.0;
       }
       else if (5000.0 <= altitude && altitude < 6000.0)
       {
           D0 = 0.7364;
           D1 = 0.6601;
           B0 = 5000.0;
           B1 = 6000.0;
       }
       else if (6000.0 <= altitude && altitude < 7000.0)
       {
           D0 = 0.6601;
           D1 = 0.5900;
           B0 = 6000.0;
           B1 = 7000.0;
       }
       else if (7000.0 <= altitude && altitude < 8000.0)
       {
           D0 = 0.5900;
           D1 = 0.5258;
           B0 = 7000.0;
           B1 = 8000.0;
       }
       else if (8000.0 <= altitude && altitude < 9000.0)
       {
           D0 = 0.5258;
           D1 = 0.4671;
           B0 = 8000.0;
           B1 = 9000.0;
       }
       else if (9000.0 <= altitude && altitude < 10000.0)
       {
           D0 = 0.4671;
           D1 = 0.4135;
           B0 = 9000.0;
           B1 = 10000.0;
       }
       else if (10000.0 <= altitude && altitude < 15000.0)
       {
           D0 = 0.4135;
           D1 = 0.1948;
           B0 = 10000.0;
           B1 = 15000.0;
       }
       else if (15000.0 <= altitude && altitude < 20000.0)
       {
           D0 = 0.1948;
           D1 = 0.08891;
           B0 = 15000.0;
           B1 = 20000.0;
       }
       else if (20000.0 <= altitude && altitude < 25000.0)
       {
           D0 = 0.08891;
           D1 = 0.04008;
           B0 = 20000.0;
           B1 = 25000.0;
       }
       else if (25000.0 <= altitude && altitude < 30000.0)
       {
           D0 = 0.04008;
           D1 = 0.01841;
           B0 = 25000.0;
           B1 = 30000.0;
       }
       else if (30000.0 <= altitude && altitude < 40000.0)
       {
           D0 = 0.01841;
           D1 = 0.003996;
           B0 = 30000.0;
           B1 = 40000.0;
       }
       else if (40000.0 <= altitude && altitude < 50000.0)
       {
           D0 = 0.003996;
           D1 = 0.001027;
           B0 = 40000.0;
           B1 = 50000.0;
       }
       else if (50000.0 <= altitude && altitude < 60000.0)
       {
           D0 = 0.001027;
           D1 = 0.0003097;
           B0 = 50000.0;
           B1 = 60000.0;
       }
       else if (60000.0 <= altitude && altitude < 70000.0)
       {
           D0 = 0.0003097;
           D1 = 0.0000828;
           B0 = 60000.0;
           B1 = 70000.0;
       }
       else if (70000.0 <= altitude && altitude < 80000.0)
       {
           D0 = 0.0000828;
           D1 = 0.0000185;
           B0 = 70000.0;
           B1 = 80000.0;
       }
       else // altitude >= 80000.0
       {
           D0 = 0.0000185;
           D1 = 0.0; // Assuming density is negligible beyond 80000m
           B0 = 80000.0;
           B1 = 90000.0; // Assuming 90000m as an upper limit
       }

       // Linear interpolation
       airDensity = linearI(altitude, B1, B0, D1, D0);
   }

   
   void simulate(double timePerIncrement, double muzzleVelocity)
   {
      double hangTime = 0.0;
      DX = computeHorizontalComponent(this->angle, muzzleVelocity);
      DY = computeVerticalComponent(this->angle, muzzleVelocity);
      double DDX = 0;
      double DDY = 0;
      gravity = -9.8;
      while (position.getMetersY() >= 0)
      {
         computeAirDensity();
         
         computeGravity();
         computeAngleFromComponents();

         double dragAcceleration = computeDrag() / mass;
         double horizontalDrag = computeHorizontalComponent(angle, dragAcceleration);
         double verticalDrag = computeVerticalComponent(angle, dragAcceleration);
         DDX = -1 * horizontalDrag;
         DDY = gravity - verticalDrag;

         DX = computeVelocity(DX, DDX, timePerIncrement);
         DY = computeVelocity(DY, DDY, timePerIncrement);

         position.setMetersX(computeDistance(position.getMetersX(), DX, DDX, timePerIncrement));
         position.setMetersY(computeDistance(position.getMetersY(), DY, DDY, timePerIncrement));

         hangTime += timePerIncrement;
      }
      
      std::cout << "Distance:" << position.getMetersX() << " Altitude" << position.getMetersY() << " Hang Time: " << hangTime << std::endl;
   }
};

