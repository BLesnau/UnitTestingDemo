#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

using namespace testing;

class INumberRetriever2
{
public:
   virtual int GetInt( int seed ) = 0;
   virtual int GetInt( std::string seed ) = 0;
};

class NumberRetriever2 : public INumberRetriever2
{
public:
   virtual int GetInt( int seed ) override { return rand() % seed; }
   virtual int GetInt( std::string seed ) override { return rand() % 10; }
};

class NumberAdder2
{
public:
   int AddNumbers( INumberRetriever2* num1, INumberRetriever2* num2, int seed1, int seed2 )
   {
      return num1->GetInt( seed1 ) + num2->GetInt( seed2 );
   }

   int AddNumbers( INumberRetriever2* num1, INumberRetriever2* num2, std::string seed1, std::string seed2 )
   {
      return num1->GetInt( seed1 ) + num2->GetInt( seed2 );
   }
};

class MockNumberRetriever2 : public INumberRetriever2
{
public:
   MOCK_METHOD1( GetInt, int( int ) );
   MOCK_METHOD1( GetInt, int( std::string ) );
};


/***************************************************
Ambiguous mock methods can be overcome by using a
type matcher.
***************************************************/
TEST( MockTestsMore, AmbiguousCallMock )
{
   NiceMock<MockNumberRetriever2> retrieverMock1;
   NiceMock<MockNumberRetriever2> retrieverMock2;

   //ON_CALL( retrieverMock1, GetInt( _ ) ).WillByDefault( Return( 2 ) );
   //ON_CALL( retrieverMock2, GetInt( _ ) ).WillByDefault( Return( 3 ) );

   //ON_CALL( retrieverMock1, GetInt( An<int>() ) ).WillByDefault( Return( 5 ) );
   //ON_CALL( retrieverMock2, GetInt( An<int>() ) ).WillByDefault( Return( 10 ) );
   //ON_CALL( retrieverMock1, GetInt( An<std::string>() ) ).WillByDefault( Return( 2 ) );
   //ON_CALL( retrieverMock2, GetInt( An<std::string>() ) ).WillByDefault( Return( 3 ) );

   NumberAdder2 adder;
   int result = adder.AddNumbers( &retrieverMock1, &retrieverMock2, 5, 10 );

   ASSERT_EQ( result, 5 );
}

/***************************************************
String Matchers
   StrEq(str) - StrNe(str)
   StrCaseEq(str) - StrCaseNe(str)
   StartsWith(str) - EndsWith(str)
   HasSubstr(str)
   ContainsRefex(str) - MatchesRegex(str)
***************************************************/
TEST( MockTestsMore, StringMatcher )
{
   NiceMock<MockNumberRetriever2> retrieverMock1;
   NiceMock<MockNumberRetriever2> retrieverMock2;

   //ON_CALL( retrieverMock1, GetInt( StartsWith( "Start" ) ) ).WillByDefault( Return( 2 ) );
   //ON_CALL( retrieverMock2, GetInt( EndsWith( "End" ) ) ).WillByDefault( Return( 3 ) );

   //ON_CALL( retrieverMock1, GetInt( Matcher<std::string>( StartsWith( "Start" ) ) ) ).WillByDefault( Return( 2 ) );
   //ON_CALL( retrieverMock2, GetInt( Matcher<std::string>( EndsWith( "End" ) ) ) ).WillByDefault( Return( 3 ) );

   NumberAdder2 adder;
   int result = adder.AddNumbers( &retrieverMock1, &retrieverMock2, "MyString", "MyString" );

   ASSERT_EQ( result, 5 );
}