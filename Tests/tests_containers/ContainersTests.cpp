#include <array>
#include <vector>


#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ContainersTests
{
	TEST_CLASS(ContainersTests)
	{
	public:
		
		TEST_METHOD( Test_std_array )
		{
			Assert::IsTrue( false );
		}

		TEST_METHOD( Test_MyArray )
		{
			Assert::IsTrue( false );
		}

		TEST_METHOD( Test_std_vector )
		{
			// push_back
			// capacity
			// size
			// at

			std::vector<int> vec;
			vec.push_back( 3 );
			Assert::AreEqual( 1, ( int )vec.capacity() );
			vec.push_back( 2 );
			Assert::AreEqual( 2, ( int )vec.capacity() );
			vec.push_back( 1 );
			Assert::AreEqual( 3, ( int )vec.capacity() );
			vec.push_back( 0 );
			Assert::AreEqual( 4, ( int )vec.capacity() );
			vec.push_back( 0 );
			Assert::AreEqual( 6, ( int )vec.capacity() );
			Assert::AreEqual( 5, ( int )vec.size() );
			Assert::AreEqual( 3, ( int )vec.at(0) );
			Assert::AreEqual( 2, ( int )vec.at(1) );
			Assert::AreEqual( 1, ( int )vec.at(2) );
			Assert::AreEqual( 0, ( int )vec.at(3) );
			struct  Functor {
				std::vector<int> vec_;
				void operator () () {
					vec_.at( 5 );
				}
			};
			Assert::ExpectException < std::out_of_range, Functor >( Functor{ vec } );

			// pop_back
			// empty

			Assert::IsTrue( !vec.empty() );
			vec.pop_back();
			Assert::AreEqual( 4, ( int )vec.size() );
			vec.pop_back();
			Assert::AreEqual( 3, ( int )vec.size() );
			vec.pop_back();
			Assert::AreEqual( 2, ( int )vec.size() );
			vec.pop_back();
			Assert::AreEqual( 1, ( int )vec.size() );
			vec.pop_back();
			Assert::AreEqual( 0, ( int )vec.size() );
			Assert::AreEqual( 6, ( int )vec.capacity() );
			Assert::IsTrue( vec.empty() );

			// reserve (about capacity)

			vec.reserve(8);
			Assert::AreEqual( 8, ( int )vec.capacity() );
			vec.reserve( 6 );															// doesn't reduce as shrink_to_fit!
			Assert::AreEqual( 8, ( int )vec.capacity() );	// doesn't reduce as shrink_to_fit!
			vec.push_back( 10 );
			Assert::AreEqual( 1, ( int )vec.size() );
			Assert::AreEqual( 10, ( int )vec.at(0) );
			vec.reserve( 16 );
			Assert::AreEqual( 16, ( int )vec.capacity() );
			Assert::AreEqual( 1, ( int )vec.size() );
			Assert::AreEqual( 10, ( int )vec.at( 0 ) );

			// clear

			vec.clear();
			Assert::AreEqual( 16, ( int )vec.capacity() );
			Assert::AreEqual( 0, ( int )vec.size() );
			vec.shrink_to_fit();
			Assert::AreEqual( 0, ( int )vec.capacity() );
			Assert::IsTrue( vec.empty() );

			// shrink_to_fit (C++11)

			vec.push_back( 11 );
			vec.push_back( 12 );
			vec.push_back( 13 );
			Assert::AreEqual( 3, ( int )vec.size() );
			vec.shrink_to_fit();
			Assert::AreEqual( 3, ( int )vec.capacity() );
			
			//resize (about size)
			vec.resize( 1 );
			Assert::AreEqual( 1, ( int )vec.size() );
			Assert::AreEqual( 3, ( int )vec.capacity() );
			Assert::AreEqual( 11, ( int )vec.at( 0 ) );
			vec.resize( 5 );
			Assert::AreEqual( 5, ( int )vec.size() );
			Assert::AreEqual( 5, ( int )vec.capacity() );
			Assert::AreEqual( 11, ( int )vec.at( 0 ) );
			vec.resize( 1, 3 );
			Assert::AreEqual( 1, ( int )vec.size() );
			Assert::AreEqual( 5, ( int )vec.capacity() );
			Assert::AreEqual( 11, ( int )vec.at( 0 ) );
			vec.resize( 7, 66 );
			Assert::AreEqual( 7, ( int )vec.size() );
			Assert::AreEqual( 7, ( int )vec.capacity() );
			Assert::AreEqual( 11, ( int )vec.at( 0 ) );
			Assert::AreEqual( 66, ( int )vec.at( 6 ) );
			Assert::AreEqual( 66, ( int )vec.at( 6 ) );
			Assert::AreEqual( 66, ( int )vec.at( 6 ) );
		}

		TEST_METHOD( Test_MyVector)
		{
			Assert::IsTrue( false );
		}

		TEST_METHOD( Test_std_list )
		{
			Assert::IsTrue( false );
		}

		TEST_METHOD( Test_MyList )
		{
			Assert::IsTrue( false );
		}

		TEST_METHOD( Test_std_set )
		{
			Assert::IsTrue( false );
		}

		TEST_METHOD( Test_MySet )
		{
			Assert::IsTrue( false );
		}

		TEST_METHOD( Test_std_unordered_set )
		{
			Assert::IsTrue( false );
		}

		TEST_METHOD( Test_MyUnorderedSet )
		{
			Assert::IsTrue( false );
		}
	};
}
