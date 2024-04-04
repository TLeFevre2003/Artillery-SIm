/**********************************************************************
 * Header File:
 *    HOWITZER
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a howitzer (aka the gun)
 ************************************************************************/

#pragma once

#include <list>
#include "angle.h"
#include "position.h"
#include "velocity.h"
#include "physics.h"
#include "uiDraw.h"
#include "projectile.h"

#pragma once

#define DEFAULT_MUZZLE_VELOCITY   827.00     // m/s


class TestHowitzer;

 /*********************************************
  * Howitzer
  * Everything we need to know about a howitzer (aka the gun)
  *********************************************/
class Howitzer
{
   public:
      // for unit tests
      friend ::TestHowitzer;

      // default constructor
      Howitzer() : muzzleVelocity(DEFAULT_MUZZLE_VELOCITY), elevation(45.0) {}

      // where is the howitzer at right now?
      Position & getPosition() { return position; }

      // generate a new position for the howitzer
      void generatePosition(const Position& posUpperRight)
      {
         double xPixels = random(posUpperRight.getPixelsX() * 0.1,
                                 posUpperRight.getPixelsX() * 0.9);
         position.setPixelsX(xPixels);
         position.setPixelsY(0);
      }
   
      // draws the howitzer
      void draw(ogstream & gout) const
      {
         gout.drawHowitzer(position, elevation.getRadians(), timeSinceLastFire);
      }

      // get the muzzle velocity
      double getMuzzleVelocity() const { return muzzleVelocity; }

      // move the angle of the howitzer
      void rotate(double radian) { elevation.addOnto(radian); }

      // raise (or lower) the howitzer
      void raise(double radian)
      {
         elevation.addOnto(elevation.isRight() ? -radian : radian);
      }

      // get the elevation
      const Angle & getElevation() const { return elevation; }
   
      // fires a projectile
      void fire(std::list<Projectile> & liveRounds, double startTime)
      {
         // Create projectile
         Projectile newRound(elevation, muzzleVelocity, position, startTime);
         // Push Projectile to liveRounds
         liveRounds.push_back(newRound);
         // set time since fired to 0
         timeSinceLastFire = 0;
      }
   
   

   private:
      Position position;      // initial position of the projectile
      double muzzleVelocity;  // muzzle velocity, defaults to 827.0 m/s
      Angle elevation;        // the elevation of the howitzer where 0 is up and positive is right.
      double timeSinceLastFire = 99.99;// helps draw the muzzle flash.
};
