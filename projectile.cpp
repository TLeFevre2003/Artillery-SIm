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


void Projectile::draw(ogstream& gout) const
{
   double age = flightPath.back().t;
   gout.drawProjectile(flightPath.back().pos, age - flightPath.back().t);
   
   for(revit=.rbegin(); revit!=num.rend(); revit++ )
         cout<< *revit<<endl;
   
}
