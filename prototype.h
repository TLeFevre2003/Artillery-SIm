#pragma once
#include "position.h"
#include <cmath>
#include <iostream>
#include <cassert>
#include <array>

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
   double dragCoefficient;
   double airDensity;
   double surfaceArea;
   double speedOfSound;
   const double mass = 46.7;

public:
   Prototype(double angle) 
   {
      this->angle = convertDegToRad(angle);
      DX = 0;
      DY = 0;
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
      return 0.5 * dragCoefficient * airDensity * computeTotalComponent(DX,DY) * computeTotalComponent(DX, DY) * surfaceArea;
   }

   double linearI(double x, double xf,double x0, double yf, double y0)
   {
      if (xf - y0 == 0)
      {
         return yf;
      }
      
      return y0 + ((x - x0) * (yf - y0) / (xf - x0));
   }
   
   void computeGravity()
   {
      double altitude = position.getMetersY();
      
      double data[][2] = {
         {0, 9.807},
         {1000, 9.804},
         {2000, 9.801},
         {3000, 9.797},
         {4000, 9.794},
         {5000, 9.791},
         {6000, 9.788},
         {7000, 9.785},
         {8000, 9.782},
         {9000, 9.779},
         {10000, 9.776},
         {15000, 9.761},
         {20000, 9.745},
         {25000, 9.73}
      };
      
      int size = sizeof(data) / sizeof(data[0]);
      
      gravity = -1 * linearInterpolate(data, size, altitude);
   }
   
   double linearInterpolate(const double data[][2], double size, double middle)
   {
      double Y0 = 0;
      double Y1 = 0;
      double X0 = 0;
      double X1 = 0;

      for (int i = 0; i < size; ++i)
      {
         if (i + 1 < size)
         {
            Y0 = data[i][1];
            Y1 = data[i + 1][1];
            X0 = data[i][0];
            X1 = data[i + 1][0];

            if (X0 <= middle && middle <= X1)
            {
                  double value = linearI(middle, X1, X0, Y1, Y0);
                  return value;
            }
         }
      }

      return Y1;
   }
   
   void computeAirDensity()
   {
      double altitude = position.getMetersY();
      double data[][2] = {
         {0.0, 1.225},
         {1000.0, 1.112},
         {2000.0, 1.007},
         {3000.0, 0.9093},
         {4000.0, 0.8194},
         {5000.0, 0.7364},
         {6000.0, 0.6601},
         {7000.0, 0.5900},
         {8000.0, 0.5258},
         {9000.0, 0.4671},
         {10000.0, 0.4135},
         {15000.0, 0.1948},
         {20000.0, 0.08891},
         {25000.0, 0.04008},
         {30000.0, 0.01841},
         {40000.0, 0.003996},
         {50000.0, 0.001027},
         {60000.0, 0.0003097},
         {70000.0, 0.0000828},
         {80000.0, 0.0000185}
      };

      int size = sizeof(data) / sizeof(data[0]);

      airDensity = linearInterpolate(data, size, altitude);
   }

   void calculateSpeedOfSound()
   {
      double altitude = position.getMetersY();
      double data[][2] = {
         {0.0, 340.0},
         {1000.0, 336.0},
         {2000.0, 332.0},
         {3000.0, 328.0},
         {4000.0, 324.0},
         {5000.0, 320.0},
         {6000.0, 316.0},
         {7000.0, 312.0},
         {8000.0, 308.0},
         {9000.0, 303.0},
         {10000.0, 299.0},
         {15000.0, 295.0},
         {20000.0, 295.0},
         {25000.0, 295.0},
         {30000.0, 305.0},
         {40000.0, 324.0}
      };
      int size = sizeof(data) / sizeof(data[0]);

      speedOfSound = linearInterpolate(data, size, altitude);
   }

   void computeDragCoefficient()
   {
      
      calculateSpeedOfSound();
      double totVel = computeTotalComponent(DX, DY);
      assert(speedOfSound >= 0);
      double machNumber = totVel / speedOfSound;
      double data[][2] = {
         {0.3, 0.1629},
         {0.5, 0.1659},
         {0.7, 0.2031},
         {0.89, 0.2597},
         {0.92, 0.3010},
         {0.96, 0.3287},
         {0.98, 0.4002},
         {1.0, 0.4258},
         {1.02, 0.4335},
         {1.06, 0.4483},
         {1.24, 0.4064},
         {1.53, 0.3663},
         {1.99, 0.2897},
         {2.87, 0.2297},
         {2.89, 0.2306},
         {5.0, 0.2656}
      };
      int size = sizeof(data) / sizeof(data[0]);

      dragCoefficient = linearInterpolate(data, size, machNumber);
   }
   
   void simulate(double timePerIncrement, double muzzleVelocity)
   {
      double hangTime = 0.0;
      DX = computeHorizontalComponent(this->angle, muzzleVelocity);
      DY = computeVerticalComponent(this->angle, muzzleVelocity);
      double DDX = 0;
      double DDY = 0;
      while (position.getMetersY() >= 0)
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

         position.setMetersX(computeDistance(position.getMetersX(), DX, DDX, timePerIncrement));
         position.setMetersY(computeDistance(position.getMetersY(), DY, DDY, timePerIncrement));

         hangTime += timePerIncrement;
      }
      
      std::cout << "Distance:" << position.getMetersX() << " Altitude" << position.getMetersY() << " Hang Time: " << hangTime << std::endl;
   }
};

