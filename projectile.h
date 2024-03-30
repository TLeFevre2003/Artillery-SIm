/**********************************************************************
 * Header File:
 *    PROJECTILE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/

#pragma once

#include <list>
#include "position.h"
#include "velocity.h"
#include "physics.h"
#include "uiDraw.h"
#include "angle.h"

#define DEFAULT_PROJECTILE_WEIGHT 46.7       // kg
#define DEFAULT_PROJECTILE_RADIUS 0.077545   // m

// forward declaration for the unit test class
class TestProjectile; 
class TestHowitzer;

 /**********************************************************************
  * Projectile
  *    Everything we need to know about a projectile
  ************************************************************************/
class Projectile
{
public:
   // Friend the unit test class
   friend ::TestProjectile;
   friend ::TestHowitzer;
   // create a new projectile with the default settings
   Projectile() : mass(DEFAULT_PROJECTILE_WEIGHT), radius(DEFAULT_PROJECTILE_RADIUS) {}
   Projectile(Angle angle, double muzzleVelocity, Position startPos) 
   {
      mass = DEFAULT_PROJECTILE_WEIGHT;
      radius = DEFAULT_PROJECTILE_RADIUS;
      Velocity v;
      v.set(angle, muzzleVelocity);
      PositionVelocityTime newPosVelocityTime = {startPos, v, 1 };
      flightPath.push_back(newPosVelocityTime);
   }


   // advance the round forward until the next unit of time
   void advance(double simulationTime) {}


   

   

private:

   // keep track of one moment in the path of the projectile
   struct PositionVelocityTime
   {
      PositionVelocityTime() : pos(), v(), t(0.0) {}
      PositionVelocityTime(Position p,Velocity v, double t) : pos(p) , v(v), t(t) {} // used chat GPT to figure this part out. 
      Position pos;
      Velocity v;
      double t;
   };

   double mass;           // weight of the M795 projectile. Defaults to 46.7 kg
   double radius;         // radius of M795 projectile. Defaults to 0.077545 m
   std::list<PositionVelocityTime> flightPath;
};
