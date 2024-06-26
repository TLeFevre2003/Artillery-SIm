/**********************************************************************
 * Header File:
 *    PROJECTILE
 * Author:
 *   Tyler LeFevre and Jason Chandler
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/

#pragma once

#include <list>
#include "velocity.h"
#include "physics.h"
#include "uiDraw.h"
#include "angle.h"

#define DEFAULT_PROJECTILE_WEIGHT 46.7       // kg
#define DEFAULT_PROJECTILE_RADIUS 0.077545   // m

// forward declaration for the unit test class
class TestProjectile; 
class TestHowitzer;
class Position;
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
   Projectile(const Angle & angle, double muzzleVelocity, const Position & startPos, double startTime);
   


   // advance the round forward until the next unit of time
   void advance(double simulationTime);
   
   // Draws the projectile
   void draw(ogstream& gout) const;

   Position getPosition() const { return flightPath.back().pos; }
   Velocity getVelocity() const { return flightPath.back().v; }
   double getHangtime() const { return flightPath.back().t - flightPath.front().t; }
   

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
