#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>

using namespace testing;

class INumberRetriever4
{
public:
   virtual int GetInt( int seed ) = 0;
};

class NumberRetriever4 : public INumberRetriever4
{
public:
   virtual int GetInt( int seed ) override { return rand() % seed; }
};

class NumberAdder4
{
public:
   int AddNumbers( INumberRetriever4* num1, INumberRetriever4* num2, int seed1, int seed2 )
   {
      return num1->GetInt( seed1 ) + num2->GetInt( seed2 );
      //return num1->GetInt( seed1 );
   }
};

class MockNumberRetriever4 : public INumberRetriever4
{
public:
   MOCK_METHOD1( GetInt, int( int ) );
};

/***************************************************
What if part of your test's success is based on mock
methods being called, not just the result that comes
out of them?

You can use EXPECT_CALL to make the actual method call
part of your test criteria
***************************************************/
TEST( ExpectCall, WillRepeatedly )
{
   NiceMock<MockNumberRetriever4> retrieverMock1;
   NiceMock<MockNumberRetriever4> retrieverMock2;

   EXPECT_CALL( retrieverMock1, GetInt( _ ) ).WillRepeatedly( Return( 5 ) );
   EXPECT_CALL( retrieverMock2, GetInt( _ ) ).WillRepeatedly( Return( 10 ) );

   NumberAdder4 adder;
   adder.AddNumbers( &retrieverMock1, &retrieverMock2, 50, 100 );
   adder.AddNumbers( &retrieverMock1, &retrieverMock2, 50, 100 );
   adder.AddNumbers( &retrieverMock1, &retrieverMock2, 50, 100 );
   adder.AddNumbers( &retrieverMock1, &retrieverMock2, 50, 100 );
}

/***************************************************
WillOnce ensures a method is called exactly one time
***************************************************/
TEST( ExpectCall, WillOnce )
{
   NiceMock<MockNumberRetriever4> retrieverMock1;
   NiceMock<MockNumberRetriever4> retrieverMock2;

   EXPECT_CALL( retrieverMock1, GetInt( _ ) ).WillOnce( Return( 5 ) );
   EXPECT_CALL( retrieverMock2, GetInt( _ ) ).WillOnce( Return( 10 ) );

   NumberAdder4 adder;
   adder.AddNumbers( &retrieverMock1, &retrieverMock2, 50, 100 );
   //adder.AddNumbers( &retrieverMock1, &retrieverMock2, 50, 100 );

   //Show what happens when the method is not called
}

/***************************************************
Times ensures a method is called exactly the number
of times that you provide
***************************************************/
TEST( ExpectCall, Times )
{
   NiceMock<MockNumberRetriever4> retrieverMock1;
   NiceMock<MockNumberRetriever4> retrieverMock2;

   EXPECT_CALL( retrieverMock1, GetInt( _ ) ).Times( 3 ).WillRepeatedly( Return( 5 ) );
   EXPECT_CALL( retrieverMock2, GetInt( _ ) ).Times( 3 ).WillRepeatedly( Return( 10 ) );

   NumberAdder4 adder;
   adder.AddNumbers( &retrieverMock1, &retrieverMock2, 50, 100 );
   //adder.AddNumbers( &retrieverMock1, &retrieverMock2, 50, 100 );
   //adder.AddNumbers( &retrieverMock1, &retrieverMock2, 50, 100 );
   //adder.AddNumbers( &retrieverMock1, &retrieverMock2, 50, 100 );
}