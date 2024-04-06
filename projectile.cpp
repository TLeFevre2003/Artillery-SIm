/***********************************************************************
 * Source File:
 *    PROJECTILE
 * Author:
 *    Tyler LeFevre and Jason Chandler
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/


 #include "projectile.h"
 #include "angle.h"
 using namespace std;


/*********************************************
 * PROJECTILE
 *  Create the projectile from angle, velocity, position and start time
 *********************************************/
Projectile::Projectile(const Angle & angle, double muzzleVelocity,const Position & startPos, double startTime) {
    // Set mass and radius
    mass = DEFAULT_PROJECTILE_WEIGHT;
    radius = DEFAULT_PROJECTILE_RADIUS;
   
    // Set the velocity based on given angle and magnitude
    Velocity v;
    v.set(angle, muzzleVelocity);
    
    // create The struct and push it on the list
    PositionVelocityTime newPosVelocityTime = {startPos, v, startTime};
    flightPath.push_back(newPosVelocityTime);
}

/*********************************************
 * PROJECTILE: ADVANCE
 * Move the projectile for a given amount of time
 *********************************************/
void Projectile::advance(double simulationTime)
{
   // find altitude
   double altitude = flightPath.back().pos.getMetersY();
   
   // calculate necessary values
   double airDensity = densityFromAltitude(altitude);
   double speedofSound = speedSoundFromAltitude(altitude);
   double dragCoefficient = dragFromMach(speedOfSoundToMach(flightPath.back().v, speedofSound));
   double gravity = -1.0 *  gravityFromAltitude(altitude);
   
   // Find the angle of projectile
   Angle a;
   a.setDxDy(flightPath.back().v.getDX(), flightPath.back().v.getDY());
   
   // Calculate the acceleration of the projectile
   double dragForce = forceFromDrag(airDensity, dragCoefficient, radius, flightPath.back().v.getSpeed());
   double dragAcceleration = -1*(dragForce / mass);
   Acceleration projectileAcceleration;
   projectileAcceleration.set(a,dragAcceleration);
   projectileAcceleration.addDDY(gravity);
   
   // Create the velocity
   Velocity newVelocity;
   newVelocity.setDX(flightPath.back().v.getDX());
   newVelocity.setDY(flightPath.back().v.getDY());
   
   // Find the new position
   Position newPosition(flightPath.back().pos);
   newPosition.add(projectileAcceleration, newVelocity, simulationTime-flightPath.back().t);
   
   // Update the velocity with current acceleration
   newVelocity.add(projectileAcceleration, simulationTime-flightPath.back().t);

   // Add new PositionVelocityTime to the flightPath
   PositionVelocityTime newPosVelocityTime = {newPosition, newVelocity, simulationTime};
   flightPath.push_back(newPosVelocityTime);
}

/*********************************************
 * PROJECTILE: DRAW
 * DRAWS THE PROJECTILE AND ITS TAIL
 *********************************************/
void Projectile::draw(ogstream& gout) const
{
   double age = flightPath.back().t;
   // Found reverse iterators from https://www.includehelp.com/stl/iterate-a-list-in-reverse-order-example-of-list-rbegin-and-list-rend-functions.aspx
  // draws the projectile with the most recent being darker
   for(auto revit = flightPath.rbegin(); revit!=flightPath.rend(); revit++ )
   {
      // Return before it draws white projectiles
      if ((age - (*revit).t) > 4)
      {
         return;
      }
      gout.drawProjectile((*revit).pos, age - (*revit).t);
   }
}
