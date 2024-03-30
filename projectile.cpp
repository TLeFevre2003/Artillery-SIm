/***********************************************************************
 * Source File:
 *    PROJECTILE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/


 #include "projectile.h"
 #include "angle.h"
 using namespace std;

Projectile::Projectile(Angle angle, double muzzleVelocity, Position startPos) {
    // Set mass and radius
    mass = DEFAULT_PROJECTILE_WEIGHT;
    radius = DEFAULT_PROJECTILE_RADIUS;
   
    // Set the velocity based on given angle and magnitude
    Velocity v;
    v.set(angle, muzzleVelocity);
    
    // create The struct and push it on the list
    PositionVelocityTime newPosVelocityTime = {startPos, v, 1};
    flightPath.push_back(newPosVelocityTime);
}


void Projectile::advance(double simulationTime)
{
   double altitude = flightPath.back().pos.getMetersY();
   
   double airDensity = densityFromAltitude(altitude);
   double speedofSound = speedSoundFromAltitude(altitude);
   
   double dragCoefficient = dragFromMach(speedOfSoundToMach(flightPath.back().v, speedofSound));
   double gravity = gravityFromAltitude(altitude);
   
   Angle a;
   a.setDxDy(flightPath.back().v.getDX(), flightPath.back().v.getDY());
   
   double dragForce = forceFromDrag(airDensity, dragCoefficient, radius, flightPath.back().v.getSpeed());
   double dragAcceleration = dragForce / mass;
   
   Acceleration projectileAcceleration;
   projectileAcceleration.set(a,dragAcceleration);
   
   projectileAcceleration.addDDY(gravity);
   
   Velocity newVelocity;
   newVelocity.setDX(flightPath.back().v.getDX());
   newVelocity.setDY(flightPath.back().v.getDY());
   newVelocity.add(projectileAcceleration, simulationTime);
   
   Position newPosition(flightPath.back().pos);
   newPosition.add(projectileAcceleration, newVelocity, simulationTime);
   
   PositionVelocityTime newPosVelocityTime = {newPosition, newVelocity, flightPath.back().t+simulationTime};
   flightPath.push_back(newPosVelocityTime);
}
