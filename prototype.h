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
   void computeAirDensity()
   {
       double altitude = postion.getMetersY();
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
   double calculateMachNumber()
   {
       double altitude = postion.getMetersY();
       double speedOfSound;
       double S0;
       double S1;
       double B0;
       double B1;

       assert(altitude >= 0);
       if (0.0 <= altitude && altitude < 1000.0)
       {
           S0 = 340.0;
           S1 = 336.0;
           B0 = 0.0;
           B1 = 1000.0;
       }
       else if (1000.0 <= altitude && altitude < 2000.0)
       {
           S0 = 336.0;
           S1 = 332.0;
           B0 = 1000.0;
           B1 = 2000.0;
       }
       else if (2000.0 <= altitude && altitude < 3000.0)
       {
           S0 = 332.0;
           S1 = 328.0;
           B0 = 2000.0;
           B1 = 3000.0;
       }
       else if (3000.0 <= altitude && altitude < 4000.0)
       {
           S0 = 328.0;
           S1 = 324.0;
           B0 = 3000.0;
           B1 = 4000.0;
       }
       else if (4000.0 <= altitude && altitude < 5000.0)
       {
           S0 = 324.0;
           S1 = 320.0;
           B0 = 4000.0;
           B1 = 5000.0;
       }
       else if (5000.0 <= altitude && altitude < 6000.0)
       {
           S0 = 320.0;
           S1 = 316.0;
           B0 = 5000.0;
           B1 = 6000.0;
       }
       else if (6000.0 <= altitude && altitude < 7000.0)
       {
           S0 = 316.0;
           S1 = 312.0;
           B0 = 6000.0;
           B1 = 7000.0;
       }
       else if (7000.0 <= altitude && altitude < 8000.0)
       {
           S0 = 312.0;
           S1 = 308.0;
           B0 = 7000.0;
           B1 = 8000.0;
       }
       else if (8000.0 <= altitude && altitude < 9000.0)
       {
           S0 = 308.0;
           S1 = 303.0;
           B0 = 8000.0;
           B1 = 9000.0;
       }
       else if (9000.0 <= altitude && altitude < 10000.0)
       {
           S0 = 303.0;
           S1 = 299.0;
           B0 = 9000.0;
           B1 = 10000.0;
       }
       else if (10000.0 <= altitude && altitude < 15000.0)
       {
           S0 = 299.0;
           S1 = 295.0;
           B0 = 10000.0;
           B1 = 15000.0;
       }
       else if (15000.0 <= altitude && altitude < 20000.0)
       {
           S0 = 295.0;
           S1 = 295.0;
           B0 = 15000.0;
           B1 = 20000.0;
       }
       else if (20000.0 <= altitude && altitude < 25000.0)
       {
           S0 = 295.0;
           S1 = 295.0;
           B0 = 20000.0;
           B1 = 25000.0;
       }
       else if (25000.0 <= altitude && altitude < 30000.0)
       {
           S0 = 295.0;
           S1 = 305.0;
           B0 = 25000.0;
           B1 = 30000.0;
       }
       else
       {
           S0 = 305.0;
           S1 = 324.0;
           B0 = 30000.0;
           B1 = 40000.0;
       }
      speedOfSound = linearI(altitude, B1, B0, S1, S0);
      return speedOfSound;

       // Now you can use speedOfSound for your calculations.
   }

   void computeDragCoefficient()
   {
       double machNumber = calculateMachNumber(); // Assuming you have a function to calculate Mach number
       double C0;
       double C1;
       double M0;
       double M1;

       assert(machNumber >= 0);

       if (0.3 <= machNumber && machNumber < 0.5)
       {
           C0 = 0.1629;
           C1 = 0.1659;
           M0 = 0.3;
           M1 = 0.5;
       }
       else if (0.5 <= machNumber && machNumber < 0.7)
       {
           C0 = 0.1659;
           C1 = 0.2031;
           M0 = 0.5;
           M1 = 0.7;
       }
       else if (0.7 <= machNumber && machNumber < 0.89)
       {
           C0 = 0.2031;
           C1 = 0.2597;
           M0 = 0.7;
           M1 = 0.89;
       }
       else if (0.89 <= machNumber && machNumber < 0.92)
       {
           C0 = 0.2597;
           C1 = 0.3010;
           M0 = 0.89;
           M1 = 0.92;
       }
       else if (0.92 <= machNumber && machNumber < 0.96)
       {
           C0 = 0.3010;
           C1 = 0.3287;
           M0 = 0.92;
           M1 = 0.96;
       }
       else if (0.96 <= machNumber && machNumber < 0.98)
       {
           C0 = 0.3287;
           C1 = 0.4002;
           M0 = 0.96;
           M1 = 0.98;
       }
       else if (0.98 <= machNumber && machNumber < 1.0)
       {
           C0 = 0.4002;
           C1 = 0.4258;
           M0 = 0.98;
           M1 = 1.0;
       }
       else if (1.0 <= machNumber && machNumber < 1.02)
       {
           C0 = 0.4258;
           C1 = 0.4335;
           M0 = 1.0;
           M1 = 1.02;
       }
       else if (1.02 <= machNumber && machNumber < 1.06)
       {
           C0 = 0.4335;
           C1 = 0.4483;
           M0 = 1.02;
           M1 = 1.06;
       }
       else if (1.06 <= machNumber && machNumber < 1.24)
       {
           C0 = 0.4483;
           C1 = 0.4064;
           M0 = 1.06;
           M1 = 1.24;
       }
       else if (1.24 <= machNumber && machNumber < 1.53)
       {
           C0 = 0.4064;
           C1 = 0.3663;
           M0 = 1.24;
           M1 = 1.53;
       }
       else if (1.53 <= machNumber && machNumber < 1.99)
       {
           C0 = 0.3663;
           C1 = 0.2897;
           M0 = 1.53;
           M1 = 1.99;
       }
       else if (1.99 <= machNumber && machNumber < 2.87)
       {
           C0 = 0.2897;
           C1 = 0.2297;
           M0 = 1.99;
           M1 = 2.87;
       }
       else if (2.87 <= machNumber && machNumber < 2.89)
       {
           C0 = 0.2297;
           C1 = 0.2306;
           M0 = 2.87;
           M1 = 2.89;
       }
       else if (2.89 <= machNumber && machNumber < 5.0)
       {
           C0 = 0.2306;
           C1 = 0.2656;
           M0 = 2.89;
           M1 = 5.0;
       }
       else // Mach number >= 5.0
       {
           // Assuming drag coefficient remains constant beyond Mach 5.0
           C0 = 0.2656;
           C1 = 0.2656;
           M0 = 5.0;
           M1 = 5.0;
       }

       // Linear interpolation
      coeffiecent = linearI(machNumber, M1, M0, C1, C0);
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
         computeAirDensity();
         computeDragCoefficient();
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

