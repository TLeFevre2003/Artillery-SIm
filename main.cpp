 /**********************************************************************
 * Source File:
 *    Lab 12: M777 Howitzer
 * Author:
 *    Tyler LeFevre and Jason Chandler
 * Summary:
 *    Simulate firing the M777 howitzer 15mm artillery piece
 ************************************************************************/
#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "simulation.h" // for SIMULATION
#include "position.h"   // for POSITION
#include "test.h"       // for the unit tests
using namespace std;


/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/

void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a simulator object. This
   // is the first step of every single callback function in OpenGL. 
   Simulator* pSim = (Simulator*)p;
   
   // Check for user input
   pSim->handleInput(pUI);
   
   // Increment time in the simulation
   pSim->incrementTime();
   
   // Update the positions for all projectiles
   pSim->updateProjectiles();
   
   // Check for projectile collisions
   pSim->detectCollision();

   // Draw all things to the screen
   ogstream gout;
   pSim->draw(gout);
}

double Position::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // unit tests
   testRunner();
  
   //// Initialize OpenGL
   Position posUpperRight;
   posUpperRight.setZoom(40.0 /* 40 meters equals 1 pixel */);
   posUpperRight.setPixelsX(700.0);
   posUpperRight.setPixelsY(500.0);
   Interface ui("M777 Howitzer Simulation", posUpperRight);

   // Initialize the simulation.
   Simulator sim(posUpperRight);


   // set everything into action
   ui.run(callBack, (void *)&sim);

   return 0;
}
