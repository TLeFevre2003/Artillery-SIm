/***********************************************************************
 * Source File:
 *    Test : Test runner
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The test runner for all the unit tests
 ************************************************************************/

#include "test.h"
#include "testPosition.h"
#include "testGround.h"
#include "testAngle.h"
#include "testVelocity.h"
#include "testAcceleration.h"
#include "testPhysics.h"
/*****************************************************************
 * TEST RUNNER
 * Runs all the unit tests
 ****************************************************************/
void testRunner()
{
   TestPosition().run();
   TestAngle().run();
   TestAcceleration().run();
   TestVelocity().run();
   TestPhysics().run();
}
