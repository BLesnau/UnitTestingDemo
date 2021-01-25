#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

/***************************************************
Isolate code we want to test

   We often don't want to execute "real" code for
   dependencies if we're doing something like talking
   to a web API or talking to a SQL database. We could
   create interfaces for these dependecies and have a
   fake implementation that is used in tests. This still
   requires us to provide fake logic for the methods in
   that class.

   Usually, a better way is to use mock classes to define
   the behavior of an interface implementation. You can
   define just the return value of a method rather than
   faking the actual logic inside of the method
***************************************************/

//class NumberRetriever
//{
//public:
//   int GetInt( int seed ) { return rand() % seed; }
//};
//
//class NumberAdder
//{
//public:
//   int AddNumbers( NumberRetriever num1, NumberRetriever num2, int seed1, int seed2 )
//   {
//      return num1.GetInt( seed1 ) + num2.GetInt( seed2 );
//   }
//};


class INumberRetriever
{
public:
   virtual int GetInt( int seed ) = 0;
};

class NumberRetriever : public INumberRetriever
{
public:
   virtual int GetInt( int seed ) override { return rand() % seed; }
};

class NumberAdder
{
public:
   int AddNumbers( INumberRetriever* num1, INumberRetriever* num2, int seed1, int seed2 )
   {
      return num1->GetInt( seed1 ) + num2->GetInt( seed2 );
   }
};


/***************************************************
Creating Mock Class

   Use MOCK_METHODn macros to provide mock declarations
   of individual methods where 'n' is the number of
   parameters that the method accepts.
***************************************************/

class MockNumberRetriever : public INumberRetriever
{
public:
   MOCK_METHOD1( GetInt, int( int ) );
};

/***************************************************
Using Mock Class

   We usually use NiceMock<> when creating mock instances
   because it allows us to get away without defining
   the behavior of every single method. More strict mocks
   exist with NaggyMock<> and StrictMock<>.

   Matchers are used to decide which parameter values
   are valid to match your mocked method call.
***************************************************/

TEST( MockTests, DefaultMock )
{
   NiceMock<MockNumberRetriever> retrieverMock1;
   NiceMock<MockNumberRetriever> retrieverMock2;

   NumberAdder adder;
   int result = adder.AddNumbers( &retrieverMock1, &retrieverMock2, 5, 10 );

   ASSERT_EQ( result, 5 );
}

/***************************************************
Underscores Match Any Value
***************************************************/
TEST( MockTests, UnderscoreMatcher )
{
   NiceMock<MockNumberRetriever> retrieverMock1;
   NiceMock<MockNumberRetriever> retrieverMock2;

   ON_CALL( retrieverMock1, GetInt( _ ) ).WillByDefault( Return( 2 ) );
   ON_CALL( retrieverMock2, GetInt( _ ) ).WillByDefault( Return( 3 ) );

   NumberAdder adder;
   int result = adder.AddNumbers( &retrieverMock1, &retrieverMock2, 5, 10 ); //Seed order does not matter

   ASSERT_EQ( result, 5 );
}

/***************************************************
Type Matchers
   An<>()
   A<>()
***************************************************/
TEST( MockTests, TypeMatcher )
{
   NiceMock<MockNumberRetriever> retrieverMock1;
   NiceMock<MockNumberRetriever> retrieverMock2;

   ON_CALL( retrieverMock1, GetInt( An<int>() ) ).WillByDefault( Return( 5 ) );
   ON_CALL( retrieverMock2, GetInt( A<int>() ) ).WillByDefault( Return( 7 ) );

   NumberAdder adder;
   int result = adder.AddNumbers( &retrieverMock1, &retrieverMock2, 5, 10 ); //Seed order does not matter

   ASSERT_EQ( result, 12 );
}

/***************************************************
You can provide specific values as a matcher
***************************************************/
TEST( MockTests, ValueMatcher )
{
   NiceMock<MockNumberRetriever> retrieverMock1;
   NiceMock<MockNumberRetriever> retrieverMock2;

   ON_CALL( retrieverMock1, GetInt( 5 ) ).WillByDefault( Return( 20 ) );
   ON_CALL( retrieverMock2, GetInt( 10 ) ).WillByDefault( Return( 40 ) );

   NumberAdder adder;
   int result = adder.AddNumbers( &retrieverMock1, &retrieverMock2, 5, 10 ); //Seed order does matter now

   ASSERT_EQ( result, 60 );
}

/***************************************************
Generic Matchers
   Eq(value) - Ne(value)
   Ge(value) - Gt(value) - Le(value) - Lt(value)
   IsTrue(value) - IsFalse(value)
   IsNull(value) - NotNull(value)
***************************************************/
TEST( MockTests, GenericMatcher )
{
   NiceMock<MockNumberRetriever> retrieverMock1;
   NiceMock<MockNumberRetriever> retrieverMock2;

   ON_CALL( retrieverMock1, GetInt( Ge( 5 ) ) ).WillByDefault( Return( 10 ) );
   ON_CALL( retrieverMock2, GetInt( Le( 10 ) ) ).WillByDefault( Return( 30 ) );

   NumberAdder adder;
   int result = adder.AddNumbers( &retrieverMock1, &retrieverMock2, 4, 11 );

   ASSERT_EQ( result, 40 );
}

/***************************************************
Composite Matchers
   AllOf( m1, m2, ... )
   AllOfArray( ... )
   AnyOf( m1, m2, ... )
   AnyOfArray( ... )
   Not( m )

***************************************************/
TEST( MockTests, CompositeMatcher )
{
   NiceMock<MockNumberRetriever> retrieverMock1;
   NiceMock<MockNumberRetriever> retrieverMock2;

   ON_CALL( retrieverMock1, GetInt( AllOf( Ge(5), Le(10) ) ) ).WillByDefault( Return( 100 ) );
   ON_CALL( retrieverMock2, GetInt( _ ) ).WillByDefault( Return( 400 ) );

   NumberAdder adder;
   int result = adder.AddNumbers( &retrieverMock1, &retrieverMock2, 4, 10 );

   ASSERT_EQ( result, 500 );
}