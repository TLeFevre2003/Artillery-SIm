#pragma once
#include "position.h"
#include <cmath>
#include <iostream>
#include <cassert>
#include <vector>
#include <iomanip>

using namespace std;
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
   double DDX;
   double DDY;
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
      DDX = 0;
      DDY = 0;
      surfaceArea = PI * 0.25 * (0.15489) * (0.15489);
   }
   double computeDistance(double s, double v, double a, double t);
   double computeAcceleration(double f, double m);
   double computeVelocity(double v, double a, double t);
   double computeVerticalComponent(double a, double total);
   double computeHorizontalComponent(double a, double total);
   double computeTotalComponent(double x, double y);
   double convertDegToRad(double d);
   void computeAngleFromComponents();
   double computeDrag();
   double linearI(double x, double xf, double x0, double yf, double y0);   
   void computeGravity();   
   double linearInterpolate(const vector<vector<double>>& data, double middle);
   void computeAirDensity();
   void calculateSpeedOfSound();
   void computeDragCoefficient();
   void simulate(double timePerIncrement, double muzzleVelocity);
  
};

