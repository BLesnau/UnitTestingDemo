#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>

using namespace testing;

class INumberRetriever5
{
public:
   virtual int GetInt( int seed ) = 0;
};

class NumberRetriever5 : public INumberRetriever5
{
public:
   virtual int GetInt( int seed ) override { return rand() % seed; }
};

class NumberAdder5
{
public:
   int AddNumbers( INumberRetriever5* num1, INumberRetriever5* num2, int seed1, int seed2 )
   {
      return num1->GetInt( seed1 ) + num2->GetInt( seed2 );
   }
};

class MockNumberRetriever5 : public INumberRetriever5
{
public:
   MOCK_METHOD1( GetInt, int( int ) );
};

/***************************************************
EXPECT_CALL Order Matters

If multiple expectations are set for a method call, 
the most recently defined one is what takes priority.
***************************************************/
TEST( ExpectCallOrder, WillRepeatedlyNewestTakePriority)
{
   NiceMock<MockNumberRetriever5> retrieverMock1;
   NiceMock<MockNumberRetriever5> retrieverMock2;

   EXPECT_CALL( retrieverMock1, GetInt( _ ) ).WillRepeatedly( Return( 5 ) );
   EXPECT_CALL( retrieverMock1, GetInt( _ ) ).WillRepeatedly( Return( 10 ) );

   EXPECT_CALL( retrieverMock2, GetInt( _ ) ).WillRepeatedly( Return( 0 ) );

   NumberAdder5 adder;
   int result = adder.AddNumbers( &retrieverMock1, &retrieverMock2, 50, 100 );

   ASSERT_EQ( result, 5 );
   //ASSERT_EQ( result, 10 );

   //result = adder.AddNumbers( &retrieverMock1, &retrieverMock2, 50, 100 );
   //ASSERT_EQ( result, 10 );
}

TEST( ExpectCallOrder, TimesNewestTakePriority )
{
   NiceMock<MockNumberRetriever5> retrieverMock1;
   NiceMock<MockNumberRetriever5> retrieverMock2;

   EXPECT_CALL( retrieverMock1, GetInt( _ ) ).WillRepeatedly( Return( 5 ) );
   EXPECT_CALL( retrieverMock1, GetInt( _ ) ).Times(2).WillRepeatedly( Return( 10 ) );
   //EXPECT_CALL( retrieverMock1, GetInt( _ ) ).Times(2).WillRepeatedly( Return( 10 ) ).RetiresOnSaturation();

   EXPECT_CALL( retrieverMock2, GetInt( _ ) ).WillRepeatedly( Return( 0 ) );

   NumberAdder5 adder;
   int result = adder.AddNumbers( &retrieverMock1, &retrieverMock2, 50, 100 );
   ASSERT_EQ( result, 10 );
   result = adder.AddNumbers( &retrieverMock1, &retrieverMock2, 50, 100 );
   ASSERT_EQ( result, 10 );

   //result = adder.AddNumbers( &retrieverMock1, &retrieverMock2, 50, 100 );
   //ASSERT_EQ( result, 5 );

   //RetiresOnSaturation() can be used to expire an expectation once it is done
}

/***************************************************
You can also ensure methods are called in a specific
order as part of your test's success. You can extend
you expectation with the InSequence() method, but the
easier method that I like better if just to define an 
InSequence object that sets a scope where all defined 
expectations are required to happen in the order that 
they are defined.
***************************************************/
TEST( ExpectCallOrder, SequenceOrder )
{
   NiceMock<MockNumberRetriever5> retrieverMock1;
   NiceMock<MockNumberRetriever5> retrieverMock2;

   //InSequence s;

   EXPECT_CALL( retrieverMock2, GetInt( _ ) ).WillRepeatedly( Return( 5 ) );
   EXPECT_CALL( retrieverMock1, GetInt( _ ) ).WillRepeatedly( Return( 10 ) );

   NumberAdder5 adder;
   adder.AddNumbers( &retrieverMock1, &retrieverMock2, 50, 100 );
}