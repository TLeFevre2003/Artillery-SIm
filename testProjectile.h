/***********************************************************************
 * Header File:
 *    TEST PROJECTILE
 * Author:
 *    <your name here>
 * Summary:
 *    All the unit tests for Projectile
 ************************************************************************/


#pragma once

#include "projectile.h"
#include "unitTest.h"


using namespace std;

/*******************************
 * TEST PROJECTILE
 * A friend class for Projectile which contains the Projectile unit tests
 ********************************/
class TestProjectile : public UnitTest
{
public:
   void run()
   {
      // Ticket 3: Setup
      defaultConstructor();

      // Ticket 4: Advance
      advance_nothing();
      advance_fall();
      advance_horizontal();
      advance_up();
      advance_diagonalUp();
      advance_diagonalDown();

      report("Projectile");
   }

private:
   double metersFromPixels = -1.0;


   /*****************************************************************
    *****************************************************************
    * CONSTRUCTOR
    *****************************************************************
    *****************************************************************/

   /*********************************************
    * name:    DEFAULT CONSTRUCTOR
    * input:   nothing
    * output:  mass=46.7, radius=0.077545 flightPath={}
    *********************************************/
   void defaultConstructor()
   {
      // setup/exercise
      Projectile p;
      // verify
      assertEquals(p.mass,46.7);
      assertEquals(p.radius, 0.077545);
      assert(p.flightPath.empty());
   } // teardown

   /*********************************************
    * name:    NON DEFAULT CONSTRUCTOR
    * input:   angle = 0.6435, magnitude = 5, start pos = (123,465) 
    * output:  mass=46.7, radius=0.077545 flightPath={first}
    * first = {pos = start pos, v = (3,4) time = 1}
    *********************************************/
   void nonDefaultConstructor()
   {    
      // setup/exercise
      Angle a;
      a.radians= 0.6435;
      double m = 5.0;
      Position startPos;
      startPos.x = 123;
      startPos.y = 456;
      //exercise
      Projectile p(a,m,startPos);
      // verify
      assertEquals(a.radians, 0.6435);
      assertEquals(m, 5.0);
      assertEquals(startPos.x, 123);
      assertEquals(startPos.y, 456);
      assertEquals(p.mass, 46.7);
      assertEquals(p.radius, 0.077545);
      assert(p.flightPath.size(),1);
      assertEquals(p.(*flightPath.begin()).pos.x, 123);
   } // teardown

   // we chose not to use the reset function because it doesn't make since for our design.
   /*****************************************************************
    *****************************************************************
    * ADVANCE
    *****************************************************************
    *****************************************************************/ 

   /*********************************************
    * name:    ADVANCE : the projectile is not fired. Nothing will happen
    * input:   flightPath={}
    * output:  flightPath={}
    *********************************************/
   void advance_nothing()
   {
      assertUnit(NOT_YET_IMPLEMENTED);
   }

   /*********************************************
    * name:    ADVANCE : the projectile is stationary and falls down
    * input:   flightPath={pos=100,200 v=0,0 t=100}
    * output:  flightPath={}{pos=100,190 v=0,-9.8 t=101}
    *********************************************/
   void advance_fall()
   {
      assertUnit(NOT_YET_IMPLEMENTED);
   }

   /*********************************************
    * name:    ADVANCE : the projectile is traveling horizontally
    * input:   flightPath={pos=100,200 v=50,0 t=100}
    * output:  flightPath={}{pos=149.9513,190 
    *                        v=49.9513,-9.8 
    *                        t=101}
    *********************************************/
   void advance_horizontal()
   {
      assertUnit(NOT_YET_IMPLEMENTED);
   }

   /*********************************************
    * name:    ADVANCE : the projectile is traveling up, no horizontal position change
    * input:   flightPath={pos=100,200 v=0,100 t=100}
    * output:  flightPath={}{pos=100,289.8042 
    *                        v=0,89.8042 
    *                        t=101}
    *********************************************/
   void advance_up()
   {
      assertUnit(NOT_YET_IMPLEMENTED);
   }

   /*********************************************
    * name:    ADVANCE : the projectile is traveling up and across
    * input:   flightPath={pos=100,200 v=50,40 t=100}
    * output:  flightPath={}{pos149.9201,230.1297 
    *                        v=49.9201,30.1297 
    *                        t=101}
    *********************************************/
   void advance_diagonalUp()
   {
      assertUnit(NOT_YET_IMPLEMENTED);
   }

   /*********************************************
    * name:    ADVANCE : the projectile is traveling down and across
    * input:   flightPath={}{}{pos=100,200 v=50,-40 t=100}
    * output:  flightPath={}{}{}{pos149.9201,150.2574
    *                            v=49.9201,-49.7425
    *                            t=101}
    *********************************************/
   void advance_diagonalDown()
   {  // setup
      setupStandardFixture();
      Position pos;
      Projectile p;
      Projectile::PositionVelocityTime pvt;
      p.flightPath.push_back(pvt);
      p.flightPath.push_back(pvt);
      pvt.pos.x = 100.0;
      pvt.pos.y = 200.0;
      pvt.v.dx = 50.0;
      pvt.v.dy = -40.0;
      pvt.t = 100.0;
      p.flightPath.push_back(pvt);
      // exercise
      p.advance(101.0);
      // verify
      assertUnit(p.flightPath.size() == 4);
      assertEquals(p.mass, 46.7);
      assertEquals(p.radius, 0.077545);
      assertUnit(!p.flightPath.empty());
      if (!p.flightPath.empty())
      {
         assertEquals(p.flightPath.back().pos.x, 149.9201);
         assertEquals(p.flightPath.back().pos.y, 150.2574);
         assertEquals(p.flightPath.back().v.dx, 49.9201);
         assertEquals(p.flightPath.back().v.dy, -49.7425);
         assertEquals(p.flightPath.back().t, 101.0);
      }
      // teardown
      teardownStandardFixture();
   }

   /*****************************************************************
    *****************************************************************
    * STANDARD FIXTURE
    *****************************************************************
    *****************************************************************/

   // setup standard fixture - set the zoom to 1100m per pixel
   void setupStandardFixture()
   {
      Position p;
      metersFromPixels = p.metersFromPixels;
      p.metersFromPixels = 1.0;
   }

   // teardown the standard fixture - reset the zoom to what it was previously
   void teardownStandardFixture()
   {
      assert(metersFromPixels != -1.0);
      Position p;
      p.metersFromPixels = metersFromPixels;
   }

};

