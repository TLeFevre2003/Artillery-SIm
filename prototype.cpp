#include "prototype.h"
#include "angle.h"     // Include the header for the Angle class
#include "velocity.h"  // Include the header for the Velocity class


#include <iostream>
using namespace std;


void Prototype::simulate(int increments, double timePerIncrement)
{


   velocity.set(angle, initialVelocity);
   cout << velocity.getDY()<<endl;
   acceleration.setDDY(-9.8);
   
   
   
   
   for (int count = 0; count < increments; count ++)
   {
      
      
      velocity.add(acceleration, timePerIncrement);

      
      
      position.addMetersX(velocity.getDX() * timePerIncrement);
      position.addMetersY(velocity.getDY() * timePerIncrement);
      
      
      
   }
   
   cout << "Distance " << position.getMetersX() << " Altitude " << position.getMetersY() << endl;
   






}

