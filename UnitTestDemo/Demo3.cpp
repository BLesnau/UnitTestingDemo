#include <gtest/gtest.h>
#include <gmock/gmock.h>

/***************************************************
ASSERT Versus EXPECT

   ASSERTs fail a test immediately even if there are
   ASSERTs further in the test

   EXPECTs collect results from all EXPECTs and report
   a pass or fail at the end of a test

   You should be able to use EXPECT almost anywhere
   you would have used ASSERT
***************************************************/

TEST( AssertVersusExpect, AssertFailEarly )
{
   int v1 = 1;
   int v2 = 2;
   int v3 = 3;
   ASSERT_EQ( v1, 1 );
   ASSERT_EQ( v2, 1 );
   ASSERT_EQ( v3, 1 );
}

TEST( AssertVersusExpect, ExpectFailLater )
{
   int v1 = 1;
   int v2 = 2;
   int v3 = 3;
   EXPECT_EQ( v1, 1 );
   EXPECT_EQ( v2, 1 );
   EXPECT_EQ( v3, 1 );
}