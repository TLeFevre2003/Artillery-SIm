/***********************************************************************
 * Header File:
 *    TEST HOWITZER
 * Author:
 *    <your name here>
 * Summary:
 *    All the unit tests for Howitzer
 ************************************************************************/


#pragma once

#include "howitzer.h"
#include "unitTest.h"

#define NOT_YET_IMPLEMENTED true

/*******************************
 * TEST HOWITZER
 * A friend class for Howitzer which contains the Howitzer unit tests
 ********************************/
class TestHowitzer : public UnitTest
{
public:
   void run()
   {
      // Ticket 1: Getters
      defaultConstructor();
      getPosition_zero();
      getPosition_middle();
      getMuzzleVelocity_slow();
      getMuzzleVelocity_standard();
      getElevation_up();
      getElevation_right();
      getElevation_left();

      // Ticket 2: Setters
      generatePosition_small();
      generatePosition_large();
      raise_rightDown();
      raise_rightUp();
      raise_leftDown();
      raise_leftUp();
      rotate_clock();
      rotate_counterClock();
      rotate_wrapClock();
      rotate_wrapCounterClock();
      
      
      // Ticket 3: Projectile Setup
      fire_right();
      fire_left();
      fire_up();

      report("Howitzer");
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
     * output:  zeros
     *********************************************/
   void defaultConstructor()
   {
      // setup/excersize
      Howitzer h;
      // verify
      assertEquals(827,h.muzzleVelocity);
      assertEquals(0.785398, h.elevation.radians);
      assertEquals(0,h.position.x);
      assertEquals(0,h.position.y);
   } // teardown

   /*****************************************************************
    *****************************************************************
    * GETTERS
    *****************************************************************
    *****************************************************************/

    /*********************************************
     * name:    GET POSITION ZERO
     * input:   h.pos=(0,0)
     * output:  pos=(0,0)
     *********************************************/
   void getPosition_zero()
   {
      // setup
      Howitzer h;
      h.position.x = 0;
      h.position.y = 0;
      double x = 99.99;
      double y = 99.99;
      // exercise
      x = h.getPosition().x;
      y = h.getPosition().y;
      // verify
      assertEquals(0, x);
      assertEquals(0, y);

      assertEquals(827, h.muzzleVelocity);
      assertEquals(0.785398, h.elevation.radians);
      assertEquals(0, h.position.x);
      assertEquals(0, h.position.y);
   } // teardown

   /*********************************************
    * name:    GET POSITION MIDDLE
     * input:   h.pos=(123.4, 567.8)
     * output:  pos=(123.4, 567.8)
    *********************************************/
   void getPosition_middle()
   {
      // setup
      Howitzer h;
      h.position.x = 123.4;
      h.position.y = 567.8;
      double x = 99.99;
      double y = 99.99;
      // exercise
      x = h.getPosition().x;
      y = h.getPosition().y;
      // verify
      assertEquals(123.4, x);
      assertEquals(567.8, y);

      assertEquals(827, h.muzzleVelocity);
      assertEquals(0.785398, h.elevation.radians);
      assertEquals(123.4, h.position.x);
      assertEquals(567.8, h.position.y);
   } // teardown

   /*********************************************
    * name:    GET MUZZLE VELOCITY - SLOW SPEED
     * input:   h.muzzleVelocity=(24.68)
     * output:  m=24.68
    *********************************************/
   void getMuzzleVelocity_slow()
   {
      // setup
      Howitzer h;
      h.muzzleVelocity = 24.68;
      double v = -99.99;
      // exercise
      v = h.getMuzzleVelocity();
      // verify
      assertEquals(v, 24.68);

      assertEquals(24.68, h.muzzleVelocity);
      assertEquals(0.785398, h.elevation.radians);
      assertEquals(0, h.position.x);
      assertEquals(0, h.position.y);
   }

   /*********************************************
    * name:    GET MUZZLE VELOCITY - STANDARD SPEED
     * input:   h.muzzleVelocity=(827.00)
     * output:  m=827
    *********************************************/
   void getMuzzleVelocity_standard()
   {
      // setup
      Howitzer h;
      h.muzzleVelocity = 827.00;
      double v = -99.99;
      // exercise
      v = h.getMuzzleVelocity();
      // verify
      assertEquals(v, 827.00);

      assertEquals(827.00, h.muzzleVelocity);
      assertEquals(0.785398, h.elevation.radians);
      assertEquals(0, h.position.x);
      assertEquals(0, h.position.y);
   } // teardown

   /*********************************************
    * name:    GET ELEVATION - up
     * input:   h.elevation=0
     * output:  e=0
    *********************************************/
   void getElevation_up()
   {
      // setup
      Howitzer h;
      h.elevation.radians = 0;
      double ang = -99.99;
      // exercise
      ang = h.getElevation().radians;
      // verify
      assertEquals(0, ang);
   } // teardown

   /*********************************************
    * name:    GET ELEVATION - right
     * input:   h.elevation=0.4
     * output:  e=0.4
    *********************************************/
   void getElevation_right()
   {
      // setup
      Howitzer h;
      h.elevation.radians = 0.4;
      double ang = -99.99;
      // exercise
      ang = h.getElevation().radians;
      // verify
      assertEquals(0.4, ang);

      assertEquals(827, h.muzzleVelocity);
      assertEquals(0.4, h.elevation.radians);
      assertEquals(0, h.position.x);
      assertEquals(0, h.position.y);
   } // teardown

   /*********************************************
    * name:    GET ELEVATION - left
     * input:   h.elevation=5.8
     * output:  e=5.8
    *********************************************/
   void getElevation_left()
   {
      // setup
      Howitzer h;
      h.elevation.radians = 5.8;
      double ang = -99.99;
      // exercise
      ang = h.getElevation().radians;
      // verify
      assertEquals(5.8, ang);

      assertEquals(827, h.muzzleVelocity);
      assertEquals(5.8, h.elevation.radians);
      assertEquals(0, h.position.x);
      assertEquals(0, h.position.y);
   } // teardown

   /*****************************************************************
    *****************************************************************
    * SETTERS
    *****************************************************************
    *****************************************************************/

    /*********************************************
     * name:    GENERATE POSITION small board
     * input:   (10px, 10px)
     * output:  0 <= x <= 9
     *********************************************/
   void generatePosition_small()
   {
      // setup
      Howitzer h;
      h.position.x = -99.99;
      h.position.y = -99.99;
      Position p;
      p.x = 10;
      p.y = 10;
      p.metersFromPixels = 1;
      // exercise
      h.generatePosition(p);
      // verify
      assert(0 <= h.position.x && h.position.x <= 9);
      assertEquals(h.position.y, 0);

      assertEquals(827, h.muzzleVelocity);
      assertEquals(0.785398, h.elevation.radians);
   } // teardown

    /*********************************************
    * name:    GENERATE POSITION large board
    * input:   (1000px, 1000px)
    * output:  0 <= x <= 900
    *********************************************/
   void generatePosition_large()
   {
      // setup
      Howitzer h;
      h.position.x = -99.99;
      h.position.y = -99.99;
      Position p;
      p.x = 1000;
      p.y = 1000;
      p.metersFromPixels = 1;
      // exercise
      h.generatePosition(p);
      // verify
      assert(0 <= h.position.x && h.position.x <= 900);
      assertEquals(h.position.y, 0);

      assertEquals(827, h.muzzleVelocity);
      assertEquals(0.785398, h.elevation.radians);
   } // teardown

   /*********************************************
    * name:    RAISE to the right/down
    * input:   h.elevation=0.5radians  raise(-0.1)
    * output:  h.elevation=0.6radians
    *********************************************/
   void raise_rightDown()
   {
      // setup
      Howitzer h;
      h.elevation.radians = 0.5;
      // exercize
      h.raise(-0.1);
      // verify
      assertEquals(h.elevation.radians, 0.6);

      assertEquals(827, h.muzzleVelocity);
      assertEquals(0, h.position.x);
      assertEquals(0, h.position.y);
   } // teardown

   /*********************************************
    * name:    RAISE to the right/up
    * input:   h.elevation=0.5radians  raise(0.1)
    * output:  h.elevation=0.4radians
    *********************************************/
   void raise_rightUp()
   {
      // setup
      Howitzer h;
      h.elevation.radians = 0.5;
      // exercize
      h.raise(0.1);
      // verify
      assertEquals(h.elevation.radians, 0.4);

      assertEquals(827, h.muzzleVelocity);
      assertEquals(0, h.position.x);
      assertEquals(0, h.position.y);
   } // teardown

   /*********************************************
    * name:    RAISE to the left down
    * input:   h.elevation=-0.5radians  raise(-0.1)
    * output:  h.elevation=5.683185radians
    *********************************************/
   void raise_leftDown()
   {
      // setup
      Howitzer h;
      h.elevation.radians = -0.5;
      // exercize
      h.raise(-0.1);
      // verify
      assertEquals(h.elevation.radians, 5.683185);

      assertEquals(827, h.muzzleVelocity);
      assertEquals(0, h.position.x);
      assertEquals(0, h.position.y);
   } // teardown

   /*********************************************
    * name:    RAISE to the left up
    * input:   h.elevation=-0.5radians  raise(0.1)
    * output:  h.elevation=5.883185radians
    *********************************************/
   void raise_leftUp()
   {
      // setup
      Howitzer h;
      h.elevation.radians = -0.5;
      // exercize
      h.raise(0.1);
      // verify
      assertEquals(h.elevation.radians, 5.883185);

      assertEquals(827, h.muzzleVelocity);
      assertEquals(0, h.position.x);
      assertEquals(0, h.position.y);
   }  // teardown

   /*********************************************
    * name:    ROTATE CLOCKWISE no wrapping
    * input:   h.elevation=1.23 rotate=.3
    * output:  h.elevation=1.53
    *********************************************/
   void rotate_clock()
   {
      // setup
      Howitzer h;
      h.elevation.radians = 1.23;
      // exercise
      h.rotate(.3);
      // verify
      assertEquals(h.elevation.radians, 1.53);

      assertEquals(827, h.muzzleVelocity);
      assertEquals(0, h.position.x);
      assertEquals(0, h.position.y);
   }  // teardown

   /*********************************************
    * name:    ROTATE COUNTER CLOCKWISE no wrapping
    * input:   h.elevation=1.23 rotate=-.3
    * output:  h.elevation=0.93
    *********************************************/
   void rotate_counterClock()
   {
      // setup
      Howitzer h;
      h.elevation.radians = 1.23;
      // exercise
      h.rotate(-.3);
      // verify
      assertEquals(h.elevation.radians, 0.93);

      assertEquals(827, h.muzzleVelocity);
      assertEquals(0, h.position.x);
      assertEquals(0, h.position.y);
   }  // teardown

   /*********************************************
    * name:    ROTATE CLOCKWISE CLOCKWISE WRAP BY 2PI
    * input:   h.elevation=6.1 rotate=.2
    * output:  h.elevation=0.016814693
    *********************************************/
   void rotate_wrapClock()
   {
      // setup
      Howitzer h;
      h.elevation.radians = 6.1;
      // exercise
      h.rotate(.2);
      // verify
      assertEquals(h.elevation.radians, 0.016814693);

      assertEquals(827, h.muzzleVelocity);
      assertEquals(0, h.position.x);
      assertEquals(0, h.position.y);
   }  // teardown

   /*********************************************
    * name:    ROTATE COUNTER CLOCKWISE WRAP BY 4PI
    * input:   h.elevation=0.1 rotate=-.2 - 4PI
    * output:  h.elevation=6.18318
    *********************************************/
   void rotate_wrapCounterClock()
   {
      // setup
      Howitzer h;
      h.elevation.radians = 0.1;
      // exercise
      h.rotate(-12.7663706144);
      // verify
      assertEquals(h.elevation.radians, 6.18318);

      assertEquals(827, h.muzzleVelocity);
      assertEquals(0, h.position.x);
      assertEquals(0, h.position.y);
   }  // teardown

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
      p.metersFromPixels = 1100.0;
   }

   // teardown the standard fixture - reset the zoom to what it was previously
   void teardownStandardFixture()
   {
      assert(metersFromPixels != -1.0);
      Position p;
      p.metersFromPixels = metersFromPixels;
   }
   
   
   /*****************************************************************
    *****************************************************************
    * FIRE
    *****************************************************************
    *****************************************************************/

   /*********************************************
    * name:    FIRE horizontally right
    * input:   angle=90  pos=(111,222) muzzleVelocity=100
    * output:  flightPath={pos=111,222 v=100,0 t=1}
    *********************************************/
   void fire_right()
   {
      // setup
      Howitzer h;
      h.elevation.radians = 1.5708;
      h.position.x = 111;
      h.position.y = 222;
      h.muzzleVelocity = 100;
      // exercise
      h.rotate(-12.7663706144);
      // verify
      assertEquals(h.elevation.radians, 6.18318);

      assertEquals(827, h.muzzleVelocity);
      assertEquals(0, h.position.x);
      assertEquals(0, h.position.y);
   }  // teardown
   

   /*********************************************
    * name:    FIRE horizontally left
    * input:   angle=-90  pos=(111,222) muzzleVelocity=100
    * output:  flightPath={pos=111,222 v=-100,0 t=1}
    *********************************************/
   void fire_left()
   {
      assertUnit(NOT_YET_IMPLEMENTED);
   }

   /*********************************************
    * name:    FIRE straight up
    * input:   angle=0  pos=(111,222) muzzleVelocity=100
    * output:  flightPath={pos=111,222 v=0,100 t=1}
    *********************************************/
   void fire_up()
   {
      assertUnit(NOT_YET_IMPLEMENTED);
   }
   
   
};
