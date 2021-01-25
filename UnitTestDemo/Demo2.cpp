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

bool IsSecondValueBetweenFirstAndThirdValue( int v1, int v2, int v3 )
{
   return (v1 < v2) && (v2 < v3);
}

TEST( PredicateAssertions, AssertPredPass )
{
   int v1 = 7;
   int v2 = 2;
   int v3 = 3;
   ASSERT_PRED3( IsSecondValueBetweenFirstAndThirdValue, v1, v2, v3 );
}

//TEST( PredicateAssertions, AssertPredFail )
//{
//   int v1 = 7;
//   int v2 = 5;
//   int v3 = 3;
//   ASSERT_PRED3( IsSecondValueBetweenFirstAndThirdValue, v1, v2, v3 );
//}
//
//TEST( PredicateAssertions, CompareFailureToBinaryAssertion )
//{
//   int v1 = 7;
//   int v2 = 5;
//   int v3 = 3;
//   ASSERT_LT( v1, v2 );
//   ASSERT_LT( v2, v3 );
//}
//
//TEST( PredicateAssertions, CompareFailureToBooleanAssertion )
//{
//   int v1 = 7;
//   int v2 = 5;
//   int v3 = 3;
//   ASSERT_TRUE( (v1 < v2) && (v2 < v3) );
//}
//
//TEST( PredicateAssertions, CompareFailureToBinaryAssertion2 )
//{
//   int v1 = 7;
//   int v2 = 5;
//   int v3 = 3;
//   ASSERT_EQ( IsSecondValueBetweenFirstAndThirdValue( v1, v2, v3 ), true );
//}
//
//TEST( PredicateAssertions, CompareFailureToBooleanAssertion2 )
//{
//   int v1 = 7;
//   int v2 = 5;
//   int v3 = 3;
//   ASSERT_TRUE( IsSecondValueBetweenFirstAndThirdValue( v1, v2, v3 ) );
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
   int v1 = 8;
   ASSERT_TRUE( IsEven( v1 ) );
}

//TEST( AssertionResults, FailMessage )
//{
//   int v1 = 7;
//   ASSERT_TRUE( IsEven( v1 ) );
//}