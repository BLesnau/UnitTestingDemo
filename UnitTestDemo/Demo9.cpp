#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>

using namespace testing;

class INumberRetriever6
{
public:
   virtual int GetInt( int seed ) = 0;
};

class NumberRetriever6 : public INumberRetriever6
{
public:
   virtual int GetInt( int seed ) override { return rand() % seed; }
};

class NumberAdder6
{
public:
   int AddNumbers( INumberRetriever6* num1, INumberRetriever6* num2, int seed1, int seed2 )
   {
      return num1->GetInt( seed1 ) + num2->GetInt( seed2 );
   }
};

class MockNumberRetriever6 : public INumberRetriever6
{
public:
   MOCK_METHOD1( GetInt, int( int ) );
};

TEST( NoTestFixtureTests, Test1 )
{
   NiceMock<MockNumberRetriever6> retrieverMock1;
   NiceMock<MockNumberRetriever6> retrieverMock2;

   ON_CALL( retrieverMock1, GetInt( _ ) ).WillByDefault( Return( 5 ) );
   ON_CALL( retrieverMock2, GetInt( _ ) ).WillByDefault( Return( 10 ) );

   NumberAdder6 adder;
   int result = adder.AddNumbers( &retrieverMock1, &retrieverMock2, 25, 17 );

   ASSERT_EQ( result, 15 );
}

TEST( NoTestFixtureTests, Test2 )
{
   NiceMock<MockNumberRetriever6> retrieverMock1;
   NiceMock<MockNumberRetriever6> retrieverMock2;

   ON_CALL( retrieverMock1, GetInt( _ ) ).WillByDefault( Return( 5 ) );
   ON_CALL( retrieverMock2, GetInt( _ ) ).WillByDefault( Return( 10 ) );

   NumberAdder6 adder;
   int result = adder.AddNumbers( &retrieverMock1, &retrieverMock2, 50, 100 );

   ASSERT_EQ( result, 15 );
}

TEST( NoTestFixtureTests, Test3 )
{
   NiceMock<MockNumberRetriever6> retrieverMock1;
   NiceMock<MockNumberRetriever6> retrieverMock2;

   ON_CALL( retrieverMock1, GetInt( _ ) ).WillByDefault( Return( 5 ) );
   ON_CALL( retrieverMock2, GetInt( _ ) ).WillByDefault( Return( 10 ) );

   NumberAdder6 adder;
   int result = adder.AddNumbers( &retrieverMock1, &retrieverMock2, -30, 10 );

   ASSERT_EQ( result, 15 );
}





class TestFixtureTests : public ::testing::Test
{
protected:

   // Called before every test is run
   virtual void SetUp() override
   {
      ON_CALL( _retrieverMock1, GetInt( _ ) ).WillByDefault( Return( 5 ) );
      ON_CALL( _retrieverMock2, GetInt( _ ) ).WillByDefault( Return( 10 ) );
   }

   // Called after every test is run
   virtual void TearDown() override
   {
   }

   // SetUpTestCase / SetUpTestSuite is called before the first test is run

   // TearDownTestCase / SetUpTestSuite is called after the final test is run

   NiceMock<MockNumberRetriever6> _retrieverMock1;
   NiceMock<MockNumberRetriever6> _retrieverMock2;
   NumberAdder6 _adder;
};

TEST_F( TestFixtureTests, Test1 )
{
   int result = _adder.AddNumbers( &_retrieverMock1, &_retrieverMock2, 25, 17 );

   ASSERT_EQ( result, 15 );
}

TEST_F( TestFixtureTests, Test2 )
{
   int result = _adder.AddNumbers( &_retrieverMock1, &_retrieverMock2, 50, 100 );

   ASSERT_EQ( result, 15 );
}

TEST_F( TestFixtureTests, Test3 )
{
   int result = _adder.AddNumbers( &_retrieverMock1, &_retrieverMock2, -30, 10 );

   ASSERT_EQ( result, 15 );
}