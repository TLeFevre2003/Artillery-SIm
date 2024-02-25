#include "prototype.h"
using namespace std;


/***************************************************
 * SIMULATE
 * Runs an artillery simulation and displays the distance and hangtime of the projectile
 **************************************************/
void Prototype::simulate(double timePerIncrement)
{
   double hangTime = 0.0;
   DX = computeHorizontalComponent(this->angle, muzzleVelocity);
   DY = computeVerticalComponent(this->angle, muzzleVelocity);

   double prevy = 0;
   double prevx = 0;

   while (position.getMetersY() >= 0)
   {
      computeAirDensity();
      calculateSpeedOfSound();
      computeDragCoefficient();
      computeGravity();
      computeAngleFromComponents();

      double dragAcceleration = computeDrag() / mass;
      double horizontalDrag = computeHorizontalComponent(angle, dragAcceleration);
      double verticalDrag = computeVerticalComponent(angle, dragAcceleration);
      DDX = -1 * horizontalDrag;
      DDY = gravity - verticalDrag;

      DX = computeVelocity(DX, DDX, timePerIncrement);
      DY = computeVelocity(DY, DDY, timePerIncrement);

      prevy = position.getMetersY();
      prevx = position.getMetersX();

      position.setMetersX(computeDistance(position.getMetersX(), DX, DDX, timePerIncrement));
      position.setMetersY(computeDistance(position.getMetersY(), DY, DDY, timePerIncrement));

      hangTime += timePerIncrement;
   }


   double newHangTime = LinearInterpolate(0.0, position.getMetersY(), prevy, hangTime, (hangTime - .01));
   position.setMetersX(LinearInterpolate(newHangTime, hangTime, hangTime - .01, position.getMetersX(), prevx));

   cout.setf(ios::fixed | ios::showpoint);
   cout.precision(1);
   
   cout << "Distance: " << position.getMetersX() << "m     "
      << "Hang Time: " << fixed << hangTime << "s"
      << endl;
}
/***************************************************
 * COMPUTE DRAG COEFFICIENT
 * Find the drag coefficient given the speed of sound and a given speed.
 **************************************************/
void Prototype::computeDragCoefficient()
{

   double totalVelocity = computeTotalComponent(DX, DY);
   assert(speedOfSound >= 0);
   double machNumber = totalVelocity / speedOfSound;
   vector<vector<double>> data = {
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

   dragCoefficient = LinearIntepolateWithData(data, machNumber);
}
/***************************************************
 * COMPUTE SPEED OF SOUND
 * Find the speed of sound for a given altitude
 **************************************************/
void Prototype::calculateSpeedOfSound()
{
   vector<vector<double>> data = {
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
      {40000.0, 324.0}
   };

   speedOfSound = LinearIntepolateWithData(data, position.getMetersY());
}
/***************************************************
 * COMPUTE AIR DENSITY
 * Find the air density for a given altitude
 **************************************************/
void Prototype::computeAirDensity()
{
   vector<vector<double>> data = {
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


   airDensity = LinearIntepolateWithData(data, position.getMetersY());
}
/***************************************************
 * LINEAR INTERPOLATE WITH DATA
 * Find the value of the middle point between two points
 **************************************************/
double Prototype::LinearIntepolateWithData(const vector<vector<double>>& data, double middle)
{
   double Y0 = 0;
   double Y1 = 0;
   double X0 = 0;
   double X1 = 0;

   int size = data.size();

   for (int i = 0; i < size; ++i)
   {
      if (i + 1 < size)
      {
         Y0 = data[i][1];
         Y1 = data[i + 1][1];
         X0 = data[i][0];
         X1 = data[i + 1][0];

         if (X0 <= middle && middle <= X1)
         {
            double value = LinearInterpolate(middle, X1, X0, Y1, Y0);
            return value;
         }
      }
   }

   return Y1;
}
/***************************************************
 * COMPUTE GRAVITY
 * Find the value of gravity for a given altitude
 **************************************************/
void Prototype::computeGravity()
{

   vector<vector<double>> data = {
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

   gravity = -1 * LinearIntepolateWithData(data, position.getMetersY());
}
/***************************************************
 * LINEAR INTERPOLATE
 * Find the value of the middle point
 * (r - r0)(d - d0)=(r1 - r0)(d1 - d0)
 * INPUT
 *    d0,r0 = coordinates of one point
 *    d1,r1 = coordinates of a second point
 * OUTPUT
 *     d,r = coordinates of a point in the middle
 **************************************************/

double Prototype::LinearInterpolate(double x, double xf, double x0, double yf, double y0)
{
   if (xf - y0 == 0)
   {
      return yf;
   }

   return y0 + ((x - x0) * (yf - y0) / (xf - x0));
}
/***************************************************
 * COMPUTE DRAG
 * Compute the drag in newtons:
 *     d = ½ c ρ v^2 a
 * INPUT
 *     c = drag coefficient
 *     ρ = density of the fluid/gas
 *     v = velocity of the projectile
 *     a = surface area
 * OUTPUT
 *     d : force in newtons
 **************************************************/
double Prototype::computeDrag()
{
   return 0.5 * dragCoefficient * airDensity * computeTotalComponent(DX, DY) * computeTotalComponent(DX, DY) * surfaceArea;
}
/***************************************************
 * COMPUTE ANGLE FROM COMPONENTS
 * Compute the angle from the x and y velocity:
 *     a = atan2(dx, dy)
 * INPUT
 *     dx: x velocity
 *     dy: y velocity
 * OUTPUT
 *     a : new angle
 **************************************************/
void Prototype::computeAngleFromComponents()
{
   angle = atan2(DX, DY);
}
/*************************************************
* RADIANS FROM DEGEES
* Convert degrees to radians:
*     radians / 2pi = degrees / 360
* INPUT
*     d : degrees from 0 to 360
* OUTPUT
*     r : radians from 0 to 2pi
**************************************************/
double Prototype::convertDegToRad(double d)
{
   return (d * 2 * PI / 360.0);
}
/************************************************
* COMPUTE TOTAL COMPONENT
* Given the horizontal and vertical components of
* something (velocity or acceleration), determine
* the total component. To do this, use the Pythagorean Theorem:
*    x^2 + y^2 = t^2
* where:
*      x
*    +-----
*    |   /
*  y |  / total
*    | /
*    |/
* INPUT
*    x : horizontal component
*    y : vertical component
* OUTPUT
*    total : total component
***********************************************/
double Prototype::computeTotalComponent(double x, double y)
{
   return sqrt(x * x + y * y);
}
/***********************************************
* COMPUTE HORIZONTAL COMPONENT
* Find the horizontal component of a velocity or acceleration.
* The equation is:
*     sin(a) = x / total
* This can be expressed graphically:
*      x
*    +-----
*    |   /
*  y |  / total
*    |a/
*    |/
* INPUT
*     a : angle, in radians
*     total : total velocity or acceleration
* OUTPUT
*     x : the vertical component of the total
***********************************************/
double Prototype::computeHorizontalComponent(double a, double total)
{
   return total * sin(a);
}
/***********************************************
* COMPUTE VERTICAL COMPONENT
* Find the vertical component of a velocity or acceleration.
* The equation is:
*     cos(a) = y / total
* This can be expressed graphically:
*      x
*    +-----
*    |   /
*  y |  / total
*    |a/
*    |/
* INPUT
*     a : angle, in radians
*     total : total velocity or acceleration
* OUTPUT
*     y : the vertical component of the total
***********************************************/
double Prototype::computeVerticalComponent(double a, double total)
{
   return total * cos(a);
}
/***********************************************
* COMPUTE VELOCITY
* Starting with a given velocity, find the new
* velocity once acceleration is applied. This is
* called the Kinematics equation. The
* equation is:
*     v = v + a t
* INPUT
*     v : velocity, in meters/second
*     a : acceleration, in meters/second^2
*     t : time, in seconds
* OUTPUT
*     v : new velocity, in meters/second
***********************************************/
double Prototype::computeVelocity(double v, double a, double t)
{
   return v + (a * t);
}
/**************************************************
 * COMPUTE ACCELERATION
 * Find the acceleration given a thrust and mass.
 * This will be done using Newton's second law of motion:
 *     f = m * a
 * INPUT
 *     f : force, in Newtons (kg * m / s^2)
 *     m : mass, in kilograms
 * OUTPUT
 *     a : acceleration, in meters/second^2
 ***************************************************/
double Prototype::computeAcceleration(double f, double m)
{
   return (f / m);
}
/***************************************************
 * COMPUTE DISTANCE
 * Apply inertia to compute a new position using the distance equation.
 * The equation is:
 *     s = s + v t + 1/2 a t^2
 * INPUT
 *     s : original position, in meters
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     s : new position, in meters
 **************************************************/
double Prototype::computeDistance(double s, double v, double a, double t)
{
   return s + (v * t) + (0.5 * a * t * t);
}
