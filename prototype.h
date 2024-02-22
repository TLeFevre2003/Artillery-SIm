#pragma once
#include "angle.h"
#include "velocity.h"
#include "position.h"
#include "acceleration.h"

/*****************************
*PROTOTYPE
* authors: Jason Chandler, Tyler Lefevre
* This is a class we made to give oursselves a clean workingspace to complete lab 7.
*****************************/
class Prototype
{
private:
   Angle angle;
   Velocity velocity;
   Position position;
   Acceleration acceleration;
   double initialVelocity = 827.0;
   

public:
   Prototype(double angle) {this->angle.setDegrees(angle);}
   
   void simulate(int increments, double timePerIncrement);
};

