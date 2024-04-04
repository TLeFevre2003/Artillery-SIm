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
      howitzer.generatePosition(posUpperRight);
      ground.reset(howitzer.getPosition());
      howitzer.fire(liveRounds, 1);
      liveRounds.back().advance(1.2);
      liveRounds.back().advance(1.4);
      liveRounds.back().advance(1.6);
      liveRounds.back().advance(1.8);
      liveRounds.back().advance(2.0);
      liveRounds.back().advance(2.2);
      liveRounds.back().advance(2.4);
   }
   
   // Draw everything
   void draw(ogstream & gout) const;

private:
   std::list<Projectile> liveRounds;
   Position posUpperRight;
   Ground ground;
   Howitzer howitzer;
};
