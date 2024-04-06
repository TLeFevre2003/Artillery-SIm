/**********************************************************************
 * Suurce File:
 *    SIMULATION
 * Author:
 *    Tyler LeFevre and Jason Chandler
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#include "simulation.h"  // for SIMULATION
#include <cmath>         // For absolute value
#include <iomanip>       // for fixed and setprecision
using namespace std;

#define ROTATION_AMOUNT 0.05
#define RAISE_AMOUNT 0.003

/*********************************************
 * SIMULATOR: DRAW
 * Draws the Howitzer and ground
 *********************************************/
void Simulator::draw(ogstream & gout) const
{
   ground.draw(gout);
   howitzer.draw(gout);
   
   // Draw each projectile and display their info.
   for (auto it = liveRounds.begin(); it != liveRounds.end(); ++it)
   {
      Position projectilePos = it->getPosition();
      it->draw(gout);
      gout.setPosition(projectilePos);
      gout << "Altitude: " << fixed << setprecision(1) << projectilePos.getMetersY() << "m" << endl
      << "Speed: " << it->getVelocity().getSpeed() << "m/s" << endl
      << "Distance: "  << abs((projectilePos.getMetersX() - howitzer.getPosition().getMetersX())) << "m" << endl
      << "Hangtime: " << it->getHangtime() << "s";
   }
   
   // Display the angle of the Howitzer
   gout << fixed << setprecision(1); // Set precision for the angle text
   Position angleTxt(17500,19000);
   gout.setPosition(angleTxt);
   gout << " Howitzer Angle: "<< howitzer.getElevation().getDegrees() << " Degrees";
}

/*********************************************
 * SIMULATOR: HANDLE INPUT
 * Reacts to user input to rotate or raise the angle of howitzer or press space to fire.
 *********************************************/
void Simulator::handleInput(const Interface* pUI)
{
   if (pUI->isSpace())
   {
      howitzer.fire(liveRounds,simTime);
   }
   
   if (pUI->isRight())
   {
      howitzer.rotate( ROTATION_AMOUNT );
   }

   if (pUI->isLeft())
   {
      howitzer.rotate(-ROTATION_AMOUNT);
   }
   
   if (pUI->isUp())
   {
      howitzer.raise(RAISE_AMOUNT);
   }

   if (pUI->isDown())
   {
      howitzer.raise(-RAISE_AMOUNT);
   }
}
/*********************************************
 * SIMULATOR: UPDATE PROJECTILES
 * Updates the position of all projectiles
 *********************************************/
void Simulator::updateProjectiles()
{
   for (auto it = liveRounds.begin(); it != liveRounds.end(); ++it)
   {
      it->advance(simTime);
   }
}
/*********************************************
 * SIMULATOR: DETECT COLLISION
 * Checks for collisions between projectiles and the ground and the target
 *********************************************/
void Simulator::detectCollision()
{
   Position target = ground.getTarget();
   // Iterate through each projectile
   for (auto it = liveRounds.begin(); it != liveRounds.end();)
   {
      Position projectilePos = it->getPosition();
      
      // Decide if the projectile has hit the ground
      if (projectilePos.getMetersY() - ground.getElevationMeters(projectilePos) <= 0.0)
      {
         // If the projectile hits the target reset the simulation
         if (projectilePos.getMetersX() >= target.getMetersX()-250 && projectilePos.getMetersX() <= target.getMetersX()+250)
         {
            reset();
            return;
         }
         
         // Remove the projectile when it hits the ground and increment the iterator
         it = liveRounds.erase(it);
      }
      
      // If the projectile didnt hit the ground move to the next projectile
      else
      {
         it++;
      }
   }
}

/*********************************************
 * SIMULATOR: RESET
 * Resets the position of the howitzer, resets the ground,
 * sets time to 0, and deletes all projectiles.
 *********************************************/
void Simulator::reset()
{
   simTime = 0.0;
   howitzer.generatePosition(posUpperRight);
   ground.reset(howitzer.getMutablePosition());
   liveRounds.clear();
}
