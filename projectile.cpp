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
   
}
