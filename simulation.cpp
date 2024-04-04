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
      it->draw(gout);
   }
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