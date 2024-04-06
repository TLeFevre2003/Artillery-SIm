/**********************************************************************
 * Header File:
 *    SIMULATION
 * Author:
 *   Tyler LeFevre and Jason Chandler
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
      this->posUpperRight = posUpperRight;
      reset();
   }

   // Reacts to the user input
   void handleInput(const Interface* pUI);

   // Updates the position of all projectiles
   void updateProjectiles();

   // Increments the time of the simulation
   void incrementTime() { simTime += FRAME_TIME; howitzer.updateTimeSinceFired(FRAME_TIME); }

   // Detects collisions
   void detectCollision();
   
   // Draw everything
   void draw(ogstream & gout) const;
   
   // Resets the simulation
   void reset();

private:
   std::list<Projectile> liveRounds;
   Position posUpperRight;
   Ground ground;
   Howitzer howitzer;
   double simTime;
};
