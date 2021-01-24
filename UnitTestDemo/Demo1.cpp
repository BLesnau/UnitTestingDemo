#include <gtest/gtest.h>
#include <gmock/gmock.h>

/***************************************************
Boolean Assertions
   ASSERT_TRUE( condition )
   ASSERT_FALSE( condition )
***************************************************/

TEST( BooleanAssertions, AssertTruePass )
{
   int val1 = 1;
   int val2 = 1;
   ASSERT_TRUE( val1 == val2 );
}

TEST( BooleanAssertions, AssertFalsePass )
{
   int val1 = 1;
   int val2 = 2;
   ASSERT_FALSE( val1 == val2 );
}

//TEST( BooleanAssertions, AssertTrueFail )
//{
//   int val1 = 1;
//   int val2 = 3;
//   ASSERT_TRUE( val1 > val2 );
//}


/***************************************************
Binary Comparison Assertions
   ASSERT_EQ( value1, value2 ) - ASSERT_NE( value1, value2 )
   ASSERT_GT( value1, value2 ) - ASSERT_LT( value1, value2 )
   ASSERT_GE( value1, value2 ) - ASSERT_LE( value1, value2 )
***************************************************/

TEST( BinaryAssertions, AssertEqPass )
{
   int val1 = 1;
   int val2 = 1;
   ASSERT_EQ( val1, val2 );
}

TEST( BinaryAssertions, AssertGtPass )
{
   int val1 = 3;
   int val2 = 1;
   ASSERT_GT( val1, val2 );
}

//TEST( BinaryAssertions, AssertGtFail )
//{
//   int val1 = 1;
//   int val2 = 3;
//   ASSERT_GT( val1, val2 );
//}


/***************************************************
String Assertions
   ASSERT_STREQ( value1, value2 ) - ASSERT_STRNE( value1, value2 )
   ASSERT_STRCASEEQ( value1, value2 ) - ASSERT_STRCASENE( value1, value2 )
***************************************************/

TEST( StringAssertions, AssertStrEqPass )
{
   auto str1 = "ThisIsAString";
   auto str2 = "ThisIsAString";
   ASSERT_STREQ( str1, str2 );
}

//TEST( StringAssertions, AssertStrEqFail )
//{
//   auto str1 = "ThisIsAString";
//   auto str2 = "ThisIsADifferentString";
//   ASSERT_STREQ( str1, str2 );
//}
//
//TEST( StringAssertions, CompareFailureToBinaryAssertion )
//{
//   auto str1 = "ThisIsAString";
//   auto str2 = "ThisIsADifferentString";
//   ASSERT_EQ( str1, str2 );
//}
//
//TEST( StringAssertions, CompareFailureToBooleanAssertion )
//{
//   auto str1 = "ThisIsAString";
//   auto str2 = "ThisIsADifferentString";
//   ASSERT_TRUE( str1 == str2 );
//}

/***************************************************
Floating-Point Assertions
   ASSERT_FLOAT_EQ( value1, value2 )
   ASSERT_DOUBLE_EQ( value1, value2 )
   ASSERT_NEAR( value1, value2, absValueError )

   These assertions help encapsulate whether or not numbers are
   close enough to each other to be considered equal because of
   things like rounding errors.

   There are no 'not equal' asserts because many floating-point 
   comparisons would technically be not equal even if they are
   very close to each other.
***************************************************/

TEST( FloatAssertions, AssertFloatEqPass )
{
   float val1 = 2.5;
   float val2 = 2.500001;
   ASSERT_FLOAT_EQ( val1, val2 );
}

//TEST( FloatAssertions, AssertFloatEqFail )
//{
//   float val1 = 2.5;
//   float val2 = 2.51;
//   ASSERT_FLOAT_EQ( val1, val2,  );
//}
//
//TEST( FloatAssertions, AssertNearFail )
//{
//   float val1 = 2.5;
//   float val2 = 2.51;
//   ASSERT_NEAR( val1, val2, .01 );
//}