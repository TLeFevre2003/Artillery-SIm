/**********************************************************************
 * Header File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#pragma once
#include "position.h"
#include "projectile.h"
#include "ground.h"
#include "howitzer.h"
#include "uiInteract.h"
#define FRAME_TIME .5


 /*********************************************
  * Simulation
  * Execute one simulation of a projectile being fired.
  *********************************************/
class Simulator
{
   friend TestHowitzer;
public:
   Simulator(const Position & posUpperRight) : ground(posUpperRight)
   {
      time = 0;
      this->posUpperRight = posUpperRight;
      howitzer.generatePosition(posUpperRight);
      ground.reset(howitzer.getPosition());
   }

   void handleInput(const Interface* pUI);

   void updateProjectiles();

   void incrementTime() { time += FRAME_TIME; howitzer.updateTimeSinceFired(FRAME_TIME); }

   void detectCollision();
   
   // Draw everything
   void draw(ogstream & gout) const;

private:
   std::list<Projectile> liveRounds;
   Position posUpperRight;
   Ground ground;
   Howitzer howitzer;
   double time;
};
