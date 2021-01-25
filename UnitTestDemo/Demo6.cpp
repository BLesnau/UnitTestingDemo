#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>

using namespace testing;

class INumberRetriever3
{
public:
   virtual int GetInt( int seed ) = 0;
};

class NumberRetriever3 : public INumberRetriever3
{
public:
   virtual int GetInt( int seed ) override { return rand() % seed; }
};

class NumberAdder3
{
public:
   std::vector<int> GetNumbers( INumberRetriever3* num1, INumberRetriever3* num2, int seed1, int seed2 )
   {
      std::vector<int> vec;
      vec.push_back( num1->GetInt( seed1 ) );
      vec.push_back( num2->GetInt( seed2 ) );
      return vec;
   }
};

class MockNumberRetriever3 : public INumberRetriever3
{
public:
   MOCK_METHOD1( GetInt, int( int ) );
};

/***************************************************
Container Matchers - e is an element or matcher
   Contains(e)
   Each(e)
   ElementsAre( e0, e1, ... ) - ElementsAreArray(array)
   UnorderedElementsAre( e0, e1, ...  ) - UnorderedElementsAreArray(array)
   IsEmpty() - SizeIs( size )
   IsSubsetOf( ... ) - IsSupersetOf( ... )

   ASSERT_THAT Can be used to check a result with matchers
***************************************************/
TEST( ContainerMatchers, ElementsAreTest )
{
   NiceMock<MockNumberRetriever3> retrieverMock1;
   NiceMock<MockNumberRetriever3> retrieverMock2;

   ON_CALL( retrieverMock1, GetInt( _ ) ).WillByDefault( Return( 5 ) );
   ON_CALL( retrieverMock2, GetInt( _ ) ).WillByDefault( Return( 10 ) );

   NumberAdder3 adder;
   std::vector<int> numbers = adder.GetNumbers( &retrieverMock1, &retrieverMock2, 50, 100 );

   ASSERT_THAT( numbers, ElementsAre( 5, 10 ) );
   //ASSERT_THAT( numbers, ElementsAre( 10, 5 ) );
   //ASSERT_THAT( numbers, UnorderedElementsAre( 10, 5 ) );
}