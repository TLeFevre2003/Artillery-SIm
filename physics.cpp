/***********************************************************************
 * Source File:
 *    PHYSICS
 * Author:
 *    <your name here>
 * Summary:
 *    Laws of motion, effects of gravity, wind resistence, etc.
 ************************************************************************/
  
 #include "physics.h"  // for the prototypes
 #include "velocity.h"
 
 /*********************************************************
 * LINEAR INTERPOLATION
 * From a list of domains and ranges, linear interpolate
 *********************************************************/
double linearInterpolation(const Mapping mapping[], int numMapping, double domain)
{
   double Y0 = 0;
   double Y1 = 0;
   double X0 = 0;
   double X1 = 0;
   
   if (domain < mapping[0].domain)
   {
      return mapping[0].range;
   }
   
   if (domain > mapping[numMapping-1].domain)
   {
      return mapping[numMapping-1].range;
   }
   
   for (int i = 0; i <numMapping; ++i)
   {
      if (i + 1 < numMapping)
      {
         Y0 = mapping[i].range;
         Y1 = mapping[i + 1].range;
         X0 = mapping[i].domain;
         X1 = mapping[i+1].domain;
         
         if (X0 <= domain && domain <= X1)
         {
            double value = linearInterpolation(X0, Y0, X1, Y1,domain);
            return value;
         }
      }
      
   }
   
   
   
   return Y0;
}

/*********************************************************
 * GRAVITY FROM ALTITUDE
 * Determine gravity coefficient based on the altitude
 *********************************************************/
double gravityFromAltitude(double altitude)
{
   const Mapping mapping[] =
   {
       {0, 9.807},
       {1000, 9.804},
       {2000, 9.801},
       {3000, 9.797},
       {4000, 9.794},
       {5000, 9.791},
       {6000, 9.788},
       {7000, 9.785},
       {8000, 9.782},
       {9000, 9.779},
       {10000, 9.776},
       {15000, 9.761},
       {20000, 9.745},
       {25000, 9.73}
   };
   
   
   return linearInterpolation(mapping, 14, altitude);
}

/*********************************************************
 * DENSITY FROM ALTITUDE
 * Determine the density of air based on the altitude
 *********************************************************/
double densityFromAltitude(double altitude)
{
   const Mapping mapping[] =
   {
      {0.0, 1.225},
      {1000.0, 1.112},
      {2000.0, 1.007},
      {3000.0, 0.9093},
      {4000.0, 0.8194},
      {5000.0, 0.7364},
      {6000.0, 0.6601},
      {7000.0, 0.5900},
      {8000.0, 0.5258},
      {9000.0, 0.4671},
      {10000.0, 0.4135},
      {15000.0, 0.1948},
      {20000.0, 0.08891},
      {25000.0, 0.04008},
      {30000.0, 0.01841},
      {40000.0, 0.003996},
      {50000.0, 0.001027},
      {60000.0, 0.0003097},
      {70000.0, 0.0000828},
      {80000.0, 0.0000185}
   };
   
   return linearInterpolation(mapping, 20, altitude);
}

/*********************************************************
 * SPEED OF SOUND FROM ALTITUDE
 * determine the speed of sound for a given altitude.
 ********************************************************/
double speedSoundFromAltitude(double altitude)
{
   const Mapping mapping[] =
   {
      {0.0, 340.0},
      {1000.0, 336.0},
      {2000.0, 332.0},
      {3000.0, 328.0},
      {4000.0, 324.0},
      {5000.0, 320.0},
      {6000.0, 316.0},
      {7000.0, 312.0},
      {8000.0, 308.0},
      {9000.0, 303.0},
      {10000.0, 299.0},
      {15000.0, 295.0},
      {20000.0, 295.0},
      {25000.0, 295.0},
      {30000.0, 305.0},
      {40000.0, 324.0},
      {50000.0,   337.0},
      {60000.0,   319.0},
      {70000.0,   289.0},
      {80000.0,   269.0}

   };
   return linearInterpolation(mapping, 16, altitude);
}


/*********************************************************
 * DRAG FROM MACH
 * Determine the drag coefficient for a M795 shell given speed in Mach
 *********************************************************/
double dragFromMach(double speedMach)
{
   const Mapping mapping[] =
   {
      {0.0    ,0.0},
      {0.3, 0.1629},
      {0.5, 0.1659},
      {0.7, 0.2031},
      {0.89, 0.2597},
      {0.92, 0.3010},
      {0.96, 0.3287},
      {0.98, 0.4002},
      {1.0, 0.4258},
      {1.02, 0.4335},
      {1.06, 0.4483},
      {1.24, 0.4064},
      {1.53, 0.3663},
      {1.99, 0.2897},
      {2.87, 0.2297},
      {2.89, 0.2306},
      {5.0, 0.2656}
   };
   return linearInterpolation(mapping, 17, speedMach);
}

/*******************************************************
 * SPEED OF SOUND TO MACH
 * input: VELOCITY, SPEED OF SOUND
 * output: MACH = VELOCITY / SPEED OF SOUND
 ********************************************************/
double speedOfSoundToMach(const Velocity & v, double speedOfSound)
{
   return v.getSpeed() / speedOfSound;
}
