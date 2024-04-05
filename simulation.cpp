/**********************************************************************
 * Suurce File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#include "simulation.h"  // for SIMULATION
#define ROTATION_AMOUNT 0.05
#define RAISE_AMOUNT 0.003

#include <iostream>
#include <iomanip>       // for fixed and setprecision
using namespace std;
/*********************************************
 * SIMULATOR: DRAW
 * Draws the Howitzer and ground
 *********************************************/
void Simulator::draw(ogstream & gout) const
{
   ground.draw(gout);
   howitzer.draw(gout);
   for (auto it = liveRounds.begin(); it != liveRounds.end(); ++it)
   {
      Position projectilePos = it->getPosition();
      it->draw(gout);
      gout.setPosition(projectilePos);
      gout << "Altitude: " << projectilePos.getMetersY() << endl << "Speed: " << it->getVelocity().getSpeed() << endl
      << "Distance: " << projectilePos.getMetersX() << endl << " Hangtime: " << it->getHangtime();
   }
   gout <<  setprecision(3);
   Position angleTxt(21000,19000);
   gout.setPosition(angleTxt);
   gout << " Howitzer Angle: "<< howitzer.getElevation().getDegrees();
   
   
}

void Simulator::handleInput(const Interface* pUI)
{
   if (pUI->isSpace())
   {
      howitzer.fire(liveRounds,time);
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
void Simulator::updateProjectiles()
{
   for (auto it = liveRounds.begin(); it != liveRounds.end(); ++it)
   {
      it->advance(time);
   }
}

void Simulator::detectCollision()
{
   Position target = ground.getTarget();
   for (auto it = liveRounds.begin(); it != liveRounds.end(); ++it)
   {
      Position projectilePos = it->getPosition();
      
      if (projectilePos.getMetersY() - ground.getElevationMeters(projectilePos) <= 0.0)
      {
         if (projectilePos.getMetersX() >= target.getMetersX()-250 && projectilePos.getMetersX() <= target.getMetersX()+250)
         {
            reset();
            return;
         }
         

         // Erase it from the list and advance the iterator
         it = liveRounds.erase(it);
      }
   }
}

void Simulator::reset()
{
   howitzer.generatePosition(posUpperRight);
   ground.reset(howitzer.getPosition());
   liveRounds.clear();
   
   
}
