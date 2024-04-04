/**********************************************************************
 * Suurce File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

 #include "simulation.h"  // for SIMULATION

/*********************************************
 * SIMULATOR: DRAW
 * Draws the Howitzer and ground
 *********************************************/
void Simulator::draw(ogstream & gout) const
{
   
   ground.draw(gout);
   howitzer.draw(gout);
   liveRounds.back().draw(gout);
}
