#include <gtest/gtest.h>
#include <gmock/gmock.h>

/***************************************************
Boolean Assertions
   ASSERT_TRUE( condition )
   ASSERT_FALSE( condition )
***************************************************/

TEST( BooleanAssertions, AssertTruePass )
{
   int v1 = 1;
   int v2 = 1;
   ASSERT_TRUE( v1 == v2 );
}

TEST( BooleanAssertions, AssertFalsePass )
{
   int v1 = 1;
   int v2 = 2;
   ASSERT_FALSE( v1 == v2 );
}

//TEST( BooleanAssertions, AssertTrueFail )
//{
//   int v1 = 1;
//   int v2 = 3;
//   ASSERT_TRUE( v1 > v2 );
//}


/***************************************************
Binary Comparison Assertions
   ASSERT_EQ( value1, value2 ) - ASSERT_NE( value1, value2 )
   ASSERT_GT( value1, value2 ) - ASSERT_LT( value1, value2 )
   ASSERT_GE( value1, value2 ) - ASSERT_LE( value1, value2 )
***************************************************/

TEST( BinaryAssertions, AssertEqPass )
{
   int v1 = 1;
   int v2 = 1;
   ASSERT_EQ( v1, v2 );
}

TEST( BinaryAssertions, AssertGtPass )
{
   int v1 = 3;
   int v2 = 1;
   ASSERT_GT( v1, v2 );
}

//TEST( BinaryAssertions, AssertGtFail )
//{
//   int v1 = 1;
//   int v2 = 3;
//   ASSERT_GT( v1, v2 );
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
   float v1 = 2.5;
   float v2 = 2.500001;
   ASSERT_FLOAT_EQ( v1, v2 );
}

//TEST( FloatAssertions, AssertFloatEqFail )
//{
//   float v1 = 2.5;
//   float v2 = 2.51;
//   ASSERT_FLOAT_EQ( v1, v2 );
//}
//
//TEST( FloatAssertions, AssertNearPass )
//{
//   float v1 = 2.5;
//   float v2 = 2.51;
//   ASSERT_NEAR( v1, v2, .01 );
//}