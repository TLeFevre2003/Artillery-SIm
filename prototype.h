#pragma once
#include "position.h"
#include <cmath>
#include <cassert>
#include <vector>

using namespace std;
/*****************************
*PROTOTYPE
* authors: Jason Chandler, Tyler Lefevre
* This is a class we made to give oursselves a clean workingspace to complete lab 7.
*****************************/
class Prototype
{
private:

public:
   Prototype()             : angle(convertDegToRad(0.0))   {}
   Prototype(double angle) : angle(convertDegToRad(angle)) {}

   void simulate(double timePerIncrement);
   
private:
   // Equations
   double computeDistance(double s, double v, double a, double t);
   double computeAcceleration(double f, double m);
   double computeVelocity(double v, double a, double t);
   double computeVerticalComponent(double a, double total);
   double computeHorizontalComponent(double a, double total);
   double computeTotalComponent(double x, double y);
   double convertDegToRad(double d);
   void computeAngleFromComponents();
   double computeDrag();
   double LinearInterpolate(double x, double xf, double x0, double yf, double y0);
   void computeGravity();
   double LinearIntepolateWithData(const vector<vector<double>>& data, double middle);
   void computeAirDensity();
   void calculateSpeedOfSound();
   void computeDragCoefficient();
   
   
   Position position;
   const double PI = 3.14159265389;
   double angle;
   double DX = 0;
   double DY = 0;
   double DDX = 0;
   double DDY = 0;
   double gravity;
   double dragCoefficient;
   double airDensity;
   double surfaceArea = PI * 0.25 * (0.15489) * (0.15489);
   double speedOfSound;
   const double mass = 46.7;
   double muzzleVelocity = 827.0;
  
};

