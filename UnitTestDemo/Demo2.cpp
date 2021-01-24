#include <gtest/gtest.h>
#include <gmock/gmock.h>

/***************************************************
Predicate Assertions
   ASSERT_PRED1( method, val1 )
   ASSERT_PRED2( method, val1, val2 )
   ...
   ASSERT_PRED5( method, val1, ..., val5 )


   Can provide better output when specific assertions
   are not available for the values that you are verifying
***************************************************/

bool IsSecondValueBetweenFirstAndThirdValue( int val1, int val2, int val3 )
{
   return (val1 < val2) && (val2 < val3);
}

TEST( PredicateAssertions, AssertPredPass )
{
   int val1 = 1;
   int val2 = 2;
   int val3 = 3;
   ASSERT_PRED3( IsSecondValueBetweenFirstAndThirdValue, val1, val2, val3 );
}

//TEST( PredicateAssertions, AssertPredFail )
//{
//   int val1 = 1;
//   int val2 = 5;
//   int val3 = 3;
//   ASSERT_PRED3( IsSecondValueBetweenFirstAndThirdValue, val1, val2, val3 );
//}
//
//TEST( PredicateAssertions, CompareFailureToBinaryAssertion )
//{
//   int val1 = 1;
//   int val2 = 5;
//   int val3 = 3;
//   ASSERT_LT( val1, val2 );
//   ASSERT_LT( val2, val3 );
//}
//
//TEST( PredicateAssertions, CompareFailureToBooleanAssertion )
//{
//   int val1 = 1;
//   int val2 = 5;
//   int val3 = 3;
//   ASSERT_TRUE( (val1 < val2) && (val2 < val3) );
//}
//
//TEST( PredicateAssertions, CompareFailureToBinaryAssertion2 )
//{
//   int val1 = 1;
//   int val2 = 5;
//   int val3 = 3;
//   ASSERT_EQ( IsSecondValueBetweenFirstAndThirdValue( val1, val2, val3 ), true );
//}
//
//TEST( PredicateAssertions, CompareFailureToBooleanAssertion2 )
//{
//   int val1 = 1;
//   int val2 = 5;
//   int val3 = 3;
//   ASSERT_TRUE( IsSecondValueBetweenFirstAndThirdValue( val1, val2, val3 ) );
//}

/***************************************************
Even Better Output With Assertion Results
   ::testing::AssertionSuccess();
   ::testing::AssertionFailure() << "Your Message";

   Returning the above Assertion Results allows you to
   give even more specific test output.
***************************************************/

::testing::AssertionResult IsEven( int n )
{
   if ( (n % 2) == 0 )
   {
      return ::testing::AssertionSuccess();
   }
   else
   {
      return ::testing::AssertionFailure() << n << " is odd";
   }
}

TEST( AssertionResults, PassMessage )
{
   int val1 = 8;
   ASSERT_TRUE( IsEven( val1 ) );
}

//TEST( AssertionResults, FailMessage )
//{
//   int val1 = 7;
//   ASSERT_TRUE( IsEven( val1 ) );
//}