#include <array>
#include <deque>
#include <vector>



#include "../../EducationLibs/Containers/Deque.h"
#include "../../EducationLibs/Containers/ForwardList.h"
#include "../../EducationLibs/Containers/List.h"
#include "../../EducationLibs/Containers/PriorityQueue.h"
#include "../../EducationLibs/Containers/Queue.h"
#include "../../EducationLibs/Containers/Set.h"
#include "../../EducationLibs/Containers/Stack.h"
#include "../../EducationLibs/Containers/UnorderedSet.h"
#include "../../EducationLibs/Containers/Vector.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ContainersTests
{
	struct Data
	{
		int value;
		// need for Set
		bool operator > ( const Data & r ) const
		{
			return value > r.value;
		}
		bool operator < ( const Data & r ) const
		{
			return value < r.value;
		}
		// need for UnorderedSet
		struct Hash
		{
		  size_t operator()( const Data & data ) const
		  {
				return std::hash<int>{}( data.value );
		  }
		};
		struct Equal
		{
			bool operator()( const Data & l, const Data & r ) const
		  {
				return l.value == r.value;
			}
		};
		// need for test-case
		friend bool operator == ( const Data & l, const Data & r );
	};
	bool operator == ( const Data & l, const Data & r )
	{
		return l.value == r.value;
	}


	TEST_CLASS(ContainersTests)
	{
	public:
		
		TEST_METHOD( Test_std_vector )
		{
			// default_ctr
			// copy_ctr
			// move_ctr
			{
				std::vector<int> vec1{ 2, 1, 1 };
				std::vector<int> vec11( vec1 );
				Assert::IsTrue( vec1 == vec11 );

				std::vector<int> vec2( 3, 2 );
				std::vector<int> vec21( std::move( vec2 ) );
				Assert::IsTrue( vec21 == std::vector<int>{ 2, 2, 2 } );
			}

			// push_back
			// capacity
			// size
			// at

			std::vector<int> vec;
			vec.push_back( 3 );	// rvalue
			Assert::AreEqual( 1, ( int )vec.capacity() );
			vec.push_back( 2 );
			Assert::AreEqual( 2, ( int )vec.capacity() );
			vec.push_back( 1 );
			Assert::AreEqual( 3, ( int )vec.capacity() );
			vec.push_back( 0 );
			Assert::AreEqual( 4, ( int )vec.capacity() );
			int a = 0;
			vec.push_back( a );	// lvalue
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

			{
				std::vector<int> vec;
				vec.resize(1);
				auto it = vec.begin();
				//vec.resize( 16 );
				auto it2 = vec.begin();	// realloc!
				//Assert::IsTrue( it != it2 );
			}

			{
				std::vector<int> vec( 5, 3 );
				Assert::AreEqual( 5, ( int )vec.size() );
				Assert::AreEqual( 5, ( int )vec.capacity() );

				vec.resize( 1, 3 );
				Assert::AreEqual( 1, ( int )vec.size() );
				Assert::AreEqual( 5, ( int )vec.capacity() );
				Assert::AreEqual( 3, ( int )vec.at( 0 ) );

				vec.resize( 3, 66 );
				Assert::AreEqual( 3, ( int )vec.size() );
				Assert::AreEqual( 5, ( int )vec.capacity() );
				Assert::AreEqual( 3, ( int )vec.at( 0 ) );
				Assert::AreEqual( 66, ( int )vec.at( 1 ) );
				Assert::AreEqual( 66, ( int )vec.at( 2 ) );

				vec.resize( 7, 77 );
				Assert::AreEqual( 7, ( int )vec.size() );
				Assert::AreEqual( 7, ( int )vec.capacity() );
				Assert::AreEqual( 3, ( int )vec.at( 0 ) );
				Assert::AreEqual( 66, ( int )vec.at( 1 ) );
				Assert::AreEqual( 66, ( int )vec.at( 2 ) );
				Assert::AreEqual( 77, ( int )vec.at( 3 ) );
				Assert::AreEqual( 77, ( int )vec.at( 4 ) );
				Assert::AreEqual( 77, ( int )vec.at( 5 ) );
				Assert::AreEqual( 77, ( int )vec.at( 6 ) );
			}

			// default constructor
			{
				std::vector<int> vec(3);
				Assert::AreEqual( 3, ( int )vec.size() );
				Assert::AreEqual( 3, ( int )vec.capacity() );
			}

			// []
			{
				std::vector<int> vec( 3 );
				vec.push_back( 4 );
				Assert::AreEqual( 4, ( int )vec.capacity() );
				vec.push_back( 6 );
				Assert::AreEqual( 6, ( int )vec.capacity() );
				Assert::AreEqual( 4, ( int )vec[ 3 ] );
				Assert::AreEqual( 6, ( int )vec[ 4 ] );
				const std::vector<int> const_vec( 5 );
				auto & elem = const_vec[ 4 ];
				//elem = 3;	// error: const elem
			}
			{
				std::vector<int> vec;
				vec.push_back( 1 );
				Assert::AreEqual( 1, ( int )vec.capacity() );
				vec.push_back( 1 );
				Assert::AreEqual( 2, ( int )vec.capacity() );
				vec.push_back( 1 );
				Assert::AreEqual( 3, ( int )vec.capacity() );
				vec.push_back( 1 );
				Assert::AreEqual( 4, ( int )vec.capacity() );
				vec.push_back( 1 );
				Assert::AreEqual( 6, ( int )vec.capacity() );
				vec.push_back( 1 );
				Assert::AreEqual( 6, ( int )vec.capacity() );
				vec.push_back( 1 );
				Assert::AreEqual( 9, ( int )vec.capacity() );
				vec.push_back( 1 );
				vec.push_back( 1 );
				Assert::AreEqual( 9, ( int )vec.capacity() );
				vec.push_back( 1 );
				Assert::AreEqual( 13, ( int )vec.capacity() );
				vec.push_back( 1 );
				vec.push_back( 1 );
				vec.push_back( 1 );
				Assert::AreEqual( 13, ( int )vec.capacity() );
				vec.push_back( 1 );
				Assert::AreEqual( 19, ( int )vec.capacity() );
			}
			// back
			{
				std::vector<int> vec;
				vec.push_back( 1 );
				vec.push_back( 2 );
				Assert::AreEqual( 2, ( int )vec.back() );
		  }
		}

		TEST_METHOD( Test_MyVector)
		{
			// destructor
			{
				Vector<int> vec( 3, 4 );
				vec.~Vector();
				Assert::IsTrue( vec.capacity() == 0 );
				Assert::IsTrue( vec.empty() );
				Assert::IsTrue( vec.data() == nullptr );
			}

			// default_ctr
			// copy_ctr
			// move_ctr
			{
				Vector<int> vec1{ 2, 1, 1 };
				Vector<int> vec11( vec1 );
				Assert::IsTrue( vec1 == vec11 );

				Vector<int> vec2( 3, 2 );
				Vector<int> vec21( std::move( vec2 ) );
				Assert::IsTrue( vec21 == Vector<int>( 3, 2 ) );
			}

			// default_ctr
			// push_back
			// capacity
			// size
			// at
			{
			  Vector<int> vec;
			  vec.push_back( 3 );	// rvalue
			  Assert::AreEqual( 1, ( int )vec.capacity() );
			  vec.push_back( 2 );
			  Assert::AreEqual( 2, ( int )vec.capacity() );
			  vec.push_back( 1 );
			  Assert::AreEqual( 4, ( int )vec.capacity() );
			  int a = 0;
			  vec.push_back( a );	// lvalue
			  Assert::AreEqual( 4, ( int )vec.capacity() );
			  Assert::AreEqual( 4, ( int )vec.size() );
			  Assert::AreEqual( 3, ( int )vec.at( 0 ) );
			  Assert::AreEqual( 2, ( int )vec.at( 1 ) );
			  Assert::AreEqual( 1, ( int )vec.at( 2 ) );
			  Assert::AreEqual( 0, ( int )vec.at( 3 ) );
			  //todo:
			  //struct  Functor {
			  //	std::vector<int> vec_;
			  //	void operator () () {
			  //		vec_.at( 5 );
			  //	}
			  //};
			  //Assert::ExpectException < std::out_of_range, Functor >( Functor{ vec } );
			}

			// default_ctr
			// pop_back
			// empty
			{
				Vector<int> vec(4);
				Assert::AreEqual( 4, ( int )vec.size() );
				Assert::AreEqual( 4, ( int )vec.capacity() );
			  Assert::IsTrue( !vec.empty() );
			  vec.pop_back();
			  Assert::AreEqual( 3, ( int )vec.size() );
			  vec.pop_back();
			  Assert::AreEqual( 2, ( int )vec.size() );
			  vec.pop_back();
			  Assert::AreEqual( 1, ( int )vec.size() );
			  vec.pop_back();
				vec.pop_back();
			  Assert::AreEqual( 0, ( int )vec.size() );
			  Assert::AreEqual( 4, ( int )vec.capacity() );
			  Assert::IsTrue( vec.empty() );
			}

			// reserve (about capacity)
		  {
				Vector<int> vec;
		    vec.reserve( 8 );
			  Assert::AreEqual( 8, ( int )vec.capacity() );
			  vec.reserve( 6 );															// doesn't reduce as shrink_to_fit!
			  Assert::AreEqual( 8, ( int )vec.capacity() );	// doesn't reduce as shrink_to_fit!
			  vec.push_back( 10 );
			  Assert::AreEqual( 1, ( int )vec.size() );
			  Assert::AreEqual( 10, ( int )vec.at( 0 ) );
			  vec.reserve( 16 );
			  Assert::AreEqual( 16, ( int )vec.capacity() );
			  Assert::AreEqual( 1, ( int )vec.size() );
			  Assert::AreEqual( 10, ( int )vec.at( 0 ) );
		  }

			// clear
		  {
				Vector<int> vec( 16, 3 );
		    vec.clear();
			  Assert::AreEqual( 16, ( int )vec.capacity() );
			  Assert::AreEqual( 0, ( int )vec.size() );
		  }

			// shrink_to_fit (C++11)
		  {
				Vector<int> vec;
				vec.reserve( 16 );
				Assert::AreEqual( 0, ( int )vec.size() );
		    vec.push_back( 11 );
			  vec.push_back( 12 );
			  vec.push_back( 13 );
			  Assert::AreEqual( 3, ( int )vec.size() );
			  Assert::AreEqual( 16, ( int )vec.capacity() );
			  vec.shrink_to_fit();
			  Assert::AreEqual( 3, ( int )vec.capacity() );
			  vec.clear();
			  vec.shrink_to_fit();
			  Assert::AreEqual( 0, ( int )vec.capacity() );
		  }

			//resize (about size)
			{
				Vector<int> vec;
				vec.resize( 1 );
				Assert::AreEqual( 1, ( int )vec.size() );
				Assert::AreEqual( 1, ( int )vec.capacity() );
				vec.push_back( 11 );
				Assert::AreEqual( 2, ( int )vec.size() );
				Assert::AreEqual( 2, ( int )vec.capacity() );
				Assert::AreEqual( 0, ( int )vec.at( 0 ) );
				Assert::AreEqual( 11, ( int )vec.at( 1 ) );
			}
			{
				Vector<int> vec( 2, 3 );
				Assert::AreEqual( 2, ( int )vec.size() );
				Assert::AreEqual( 2, ( int )vec.capacity() );
				Assert::AreEqual( 3, ( int )vec.at( 0 ) );
				Assert::AreEqual( 3, ( int )vec.at( 1 ) );
				vec.resize( 5 );
				Assert::AreEqual( 5, ( int )vec.size() );
				Assert::AreEqual( 5, ( int )vec.capacity() );
				Assert::AreEqual( 3, ( int )vec.at( 0 ) );
				Assert::AreEqual( 3, ( int )vec.at( 1 ) );
			}
			{
				Vector<int> vec( 5, 3 );
				Assert::AreEqual( 5, ( int )vec.size() );
				Assert::AreEqual( 5, ( int )vec.capacity() );
				
			  vec.resize( 1, 3 );
			  Assert::AreEqual( 1, ( int )vec.size() );
			  Assert::AreEqual( 5, ( int )vec.capacity() );
			  Assert::AreEqual( 3, ( int )vec.at( 0 ) );

			  vec.resize( 3, 66 );
			  Assert::AreEqual( 3, ( int )vec.size() );
			  Assert::AreEqual( 5, ( int )vec.capacity() );
			  Assert::AreEqual( 3, ( int )vec.at( 0 ) );
			  Assert::AreEqual( 66, ( int )vec.at( 1 ) );
			  Assert::AreEqual( 66, ( int )vec.at( 2 ) );

				vec.resize( 7, 77 );
				Assert::AreEqual( 7, ( int )vec.size() );
				Assert::AreEqual( 7, ( int )vec.capacity() );
				Assert::AreEqual( 3, ( int )vec.at( 0 ) );
				Assert::AreEqual( 66, ( int )vec.at( 1 ) );
				Assert::AreEqual( 66, ( int )vec.at( 2 ) );
				Assert::AreEqual( 77, ( int )vec.at( 3 ) );
				Assert::AreEqual( 77, ( int )vec.at( 4 ) );
				Assert::AreEqual( 77, ( int )vec.at( 5 ) );
				Assert::AreEqual( 77, ( int )vec.at( 6 ) );
		  }
			// []
			{
				Vector<int> vec( 3 );
				vec.push_back( 4 );
				Assert::AreEqual( 6, ( int )vec.capacity() );
				vec.push_back( 6 );
				Assert::AreEqual( 4, ( int )vec[ 3 ] );
				Assert::AreEqual( 6, ( int )vec[ 4 ] );
				const Vector<int> const_vec( 5 );
				auto& elem = const_vec[ 4 ];
				//elem = 3;	// error: const elem
			}

			// back
			{
				Vector<int> vec;
				vec.push_back( 1 );
				vec.push_back( 2 );
				Assert::AreEqual( 2, ( int )vec.back() );
			}

		}

		TEST_METHOD( Test_MyList )
		{
			// push_back
			// push_front
			// size
		  {
		    List<int> list;
		    list.push_back( 1 );
		    list.push_back( 2 );
		    list.push_back( 3 );
		    list.push_front( 0 );
		    Assert::AreEqual( 4, ( int )list.size() );
		  }
			// pop_back
			// pop_front
			{
				List<int> list;
				list.push_back( 1 );
				list.push_back( 2 );
				list.push_back( 3 );
				list.pop_front();
				list.pop_back();
				Assert::AreEqual( 1, ( int )list.size() );
				Assert::AreEqual( 2, ( int )list.back() );
				Assert::AreEqual( 2, ( int )list.front() );
			}
			// back
			// front
			{
				List<int> list;
				list.push_back( 1 );
				list.push_back( 2 );
				list.push_back( 3 );
				Assert::AreEqual( 1, ( int )list.front() );
				Assert::AreEqual( 3, ( int )list.back() );
			}
			// clear
			// empty
			{
				List<int> list;
				list.push_back( 1 );
				list.push_back( 2 );
				list.push_back( 3 );
				list.clear();
				Assert::AreEqual( 0, ( int )list.size() );
				Assert::IsTrue( list.empty() );
			}
			// reverse
			{
				List<int> list;
				list.push_back( 2 );
				list.push_back( 1 );
				Assert::AreEqual( 2, ( int )list.front() );
				Assert::AreEqual( 1, ( int )list.back() );
				list.reverse();
				list.push_front( 0 );
				list.push_back( 3 );
				Assert::AreEqual( 0, ( int )list.front() );
				list.pop_front();
				Assert::AreEqual( 1, ( int )list.front() );
				list.pop_front();
				Assert::AreEqual( 2, ( int )list.front() );
				Assert::AreEqual( 3, ( int )list.back() );
			}
			// sort
		  {
				List<int> list;
				list.push_back( 8 );
				list.push_back( 3 );
				list.push_back( 5 );
				list.push_back( 2 );
				list.push_back( 1 );
				list.sort();
				Assert::AreEqual( 1, ( int )list.front() );
				list.pop_front();
				Assert::AreEqual( 2, ( int )list.front() );
				list.pop_front();
				Assert::AreEqual( 3, ( int )list.front() );
				list.pop_front();
				Assert::AreEqual( 5, ( int )list.front() );
				list.pop_front();
				Assert::AreEqual( 8, ( int )list.front() );
		  }
		}

	  TEST_METHOD( Test_MyForwardList )
		{
			// push_front
			// size
			{
				ForwardList<int> list;
				list.push_front( 3 );
				list.push_front( 4 );
				list.push_front( 5 );
				list.push_front( 6 );
				Assert::AreEqual( 4, ( int )list.size() );
			}
			// pop_front
			{
				ForwardList<int> list;
				list.push_front( 3 );
				list.push_front( 4 );
				list.push_front( 5 );
				list.push_front( 6 );
				list.pop_front();
				list.pop_front();
				list.pop_front();
				Assert::AreEqual( 1, ( int )list.size() );
				Assert::AreEqual( 3, ( int )list.front() );
			}
			// front
			{
				ForwardList<int> list;
				list.push_front( 3 );
				list.push_front( 4 );
				Assert::AreEqual( 4, ( int )list.front() );
				list.push_front( 5 );
				list.push_front( 6 );
				Assert::AreEqual( 6, ( int )list.front() );
			}
			// clear
			// empty
			{
				ForwardList<int> list;
				list.push_front( 3 );
				list.push_front( 4 );
				list.push_front( 5 );
				list.push_front( 6 );
				list.clear();
				Assert::AreEqual( 0, ( int )list.size() );
				Assert::IsTrue( list.empty() );
			}
			// reverse
			{
				ForwardList<int> list;
				list.push_front( 3 );
				list.push_front( 4 );
				list.push_front( 5 );
				list.push_front( 6 );
				Assert::AreEqual( 6, ( int )list.front() );
				list.reverse();
				Assert::AreEqual( 3, ( int )list.front() );
				list.pop_front();
				Assert::AreEqual( 4, ( int )list.front() );
				list.pop_front();
				Assert::AreEqual( 5, ( int )list.front() );
				list.pop_front();
				Assert::AreEqual( 6, ( int )list.front() );
			}
			// sort
			{
				// todo
			}
		}

		TEST_METHOD( Test_std_deque)
		{
			// at
			{
				std::deque<int> deque;
				deque.push_back( 3 );
				deque.push_back( 4 );
				deque.push_back( 5 );
				deque.push_front( 2 );
				deque.push_front( 1 );
				deque.push_front( 0 );
        for (int i = 0; i < deque.size(); ++i)
					Assert::AreEqual( i, ( int )deque[ i ] );
			}
		}
		TEST_METHOD( Test_MyDeque )
		{
			// default_ctr
			// push_back
			// push_front
			// size
		  // at
			{
				circular_array_algorithm::Deque<int> deque;
				deque.push_back( 3 );
				deque.push_back( 4 );
				deque.push_back( 5 );
				deque.push_front( 2 );
				deque.push_front( 1 );
				deque.push_front( 0 );
				for ( int i = 0; i < deque.size(); ++i )
				{
					Assert::AreEqual( i, ( int )deque[ i ] );
					Assert::AreEqual( i, ( int )deque.at( i ) );
				}
			}

			// default_ctr
			// push_back
			// push_front
			// size
			// at
			{
				like_linked_list::Deque<int> deque;
				deque.push_back( 3 );
				deque.push_back( 4 );
				deque.push_back( 5 );
				deque.push_front( 2 );
				deque.push_front( 1 );
				deque.push_front( 0 );
				for ( int i = 0; i < deque.size(); ++i )
				{
					Assert::AreEqual( i, ( int )deque[ i ] );
					Assert::AreEqual( i, ( int )deque.at( i ) );
				}
			}

			// default_ctr
			// push_back
			// capacity
			// size
			// at
			{
				like_linked_list::Deque<int> vec;
				vec.push_back( 3 );	// rvalue
				vec.push_back( 2 );
				vec.push_back( 1 );
				int a = 0;
				vec.push_back( a );	// lvalue
				Assert::AreEqual( 4, ( int )vec.size() );
				Assert::AreEqual( 3, ( int )vec.at( 0 ) );
				Assert::AreEqual( 2, ( int )vec.at( 1 ) );
				Assert::AreEqual( 1, ( int )vec.at( 2 ) );
				Assert::AreEqual( 0, ( int )vec.at( 3 ) );
			}

			// default_ctr
			// pop_back
			// empty
			{
				like_linked_list::Deque<int> vec( 4 );
				Assert::AreEqual( 4, ( int )vec.size() );
				Assert::IsTrue( !vec.empty() );
				vec.pop_back();
				Assert::AreEqual( 3, ( int )vec.size() );
				vec.pop_back();
				Assert::AreEqual( 2, ( int )vec.size() );
				vec.pop_back();
				Assert::AreEqual( 1, ( int )vec.size() );
				vec.pop_back();
				Assert::AreEqual( 0, ( int )vec.size() );
				Assert::IsTrue( vec.empty() );
			}
			// clear
			{
				like_linked_list::Deque<int> vec( 16, 3 );
				vec.clear();
				Assert::AreEqual( 0, ( int )vec.size() );
			}
			//resize (about size)
			{
				like_linked_list::Deque<int> vec;
				vec.resize( 1 );
				Assert::AreEqual( 1, ( int )vec.size() );
				vec.push_back( 11 );
				Assert::AreEqual( 2, ( int )vec.size() );
				Assert::AreEqual( 0, ( int )vec.at( 0 ) );
				Assert::AreEqual( 11, ( int )vec.at( 1 ) );
			}
			{
				like_linked_list::Deque<int> vec( 2, 3 );
				Assert::AreEqual( 2, ( int )vec.size() );
				Assert::AreEqual( 3, ( int )vec.at( 0 ) );
				Assert::AreEqual( 3, ( int )vec.at( 1 ) );
				vec.resize( 5 );
				Assert::AreEqual( 5, ( int )vec.size() );
				Assert::AreEqual( 3, ( int )vec.at( 0 ) );
				Assert::AreEqual( 3, ( int )vec.at( 1 ) );
				Assert::AreEqual( 0, ( int )vec.at( 2 ) );
				Assert::AreEqual( 0, ( int )vec.at( 3 ) );
				Assert::AreEqual( 0, ( int )vec.at( 4 ) );
			}
			{
				like_linked_list::Deque<int> vec( 5, 3 );
				Assert::AreEqual( 5, ( int )vec.size() );

				vec.resize( 1, 3 );
				Assert::AreEqual( 1, ( int )vec.size() );
				Assert::AreEqual( 3, ( int )vec.at( 0 ) );

				vec.resize( 3, 66 );
				Assert::AreEqual( 3, ( int )vec.size() );
				Assert::AreEqual( 3, ( int )vec.at( 0 ) );
				Assert::AreEqual( 66, ( int )vec.at( 1 ) );
				Assert::AreEqual( 66, ( int )vec.at( 2 ) );

				vec.resize( 7, 77 );
				Assert::AreEqual( 7, ( int )vec.size() );
				Assert::AreEqual( 3, ( int )vec.at( 0 ) );
				Assert::AreEqual( 66, ( int )vec.at( 1 ) );
				Assert::AreEqual( 66, ( int )vec.at( 2 ) );
				Assert::AreEqual( 77, ( int )vec.at( 3 ) );
				Assert::AreEqual( 77, ( int )vec.at( 4 ) );
				Assert::AreEqual( 77, ( int )vec.at( 5 ) );
				Assert::AreEqual( 77, ( int )vec.at( 6 ) );
			}
			// []
			{
				like_linked_list::Deque<int> vec( 3 );
				vec.push_back( 4 );
				vec.push_back( 6 );
				Assert::AreEqual( 4, ( int )vec[ 3 ] );
				Assert::AreEqual( 6, ( int )vec[ 4 ] );
				const like_linked_list::Deque<int> const_vec( 5 );
				auto & elem = const_vec[ 4 ];
				//elem = 3;	// error: const elem
			}

			// back
			{
				like_linked_list::Deque<int> vec;
				vec.push_back( 1 );
				vec.push_back( 2 );
				Assert::AreEqual( 2, ( int )vec.back() );
			}

			// destructor
			{
				like_linked_list::Deque<int> vec( 3, 4 );
				vec.~Deque();
				Assert::IsTrue( vec.empty() );
			}
		}
		TEST_METHOD( Test_MySet )
		{
			// insert
			// find
			// size
			// clear
			{
				Set<int> container;
				container.insert(7);
				container.insert(4);
				container.insert(11);
				container.insert(9);
				container.insert(15);
				container.insert(8);
				container.insert(10);
				Assert::AreEqual( 7, ( int )container.size() );
				auto it = container.find( 15 );
				Assert::IsTrue( it != nullptr );
				Assert::AreEqual( 15, ( int )it->data );
				it = container.find( 7 );
				Assert::IsTrue( it != nullptr );
				Assert::AreEqual( 7, ( int )it->data );
				it = container.find( 2 );
				Assert::IsTrue( it == nullptr );
				container.clear();
				Assert::IsTrue( container.empty() );
				container.insert( 7 );
				it = container.find( 7 );
				Assert::IsTrue( it != nullptr );
			}
			// erase
			{
				Set<int> container;
				container.insert( 7 );
				container.insert( 4 );
				container.insert( 2 );
        const auto isErase = static_cast< bool >( container.erase( 2 ) );
				Assert::IsTrue( isErase );
			}
			// erase
			{
				Set<int> container;
				container.insert( 20 );
				container.insert( 50 );
				container.insert( 60 );
				container.insert( 55 );
				container.insert( 57 );
				auto isErase = static_cast< bool >( container.erase( 50 ) );
				Assert::IsTrue( isErase );
				auto it = container.find( 20 );
				Assert::IsTrue( it->right->right->left->data == 57 );

				isErase = static_cast< bool >( container.erase( 60 ) );
				Assert::IsTrue( isErase );
				Assert::IsTrue( it->right->right->data == 57 );
			}
			// T.operator >, <, ==, !=
			{
				Set<Data> dataContainer;
				dataContainer.insert( Data{ 20 } );
				dataContainer.insert( Data{ 50 } );
				dataContainer.insert( Data{ 60 } );
				dataContainer.insert( Data{ 55 } );
				dataContainer.insert( Data{ 57 } );
				auto isErase = static_cast< bool >( dataContainer.erase( Data{ 50 } ) );
				Assert::IsTrue( isErase );
				auto it = dataContainer.find( Data{ 20 }  );
				Assert::IsTrue( it->right->right->left->data == Data{ 57 } );

				isErase = static_cast< bool >( dataContainer.erase( Data{ 60 } ) );
				Assert::IsTrue( isErase );
				Assert::IsTrue( it->right->right->data == Data{ 57 } );
			}
		}

		TEST_METHOD( Test_MyUnorderedSet )
		{
			//insert
			//size
			//empty
		  {
		    UnorderedSet<int> unorderedSet;
		    Assert::IsTrue( unorderedSet.size() == 0 );
		    Assert::IsTrue( unorderedSet.empty() );
		    unorderedSet.insert( 5 );
		    unorderedSet.insert( 3 );
		    unorderedSet.insert( 9 );
		    unorderedSet.insert( 1 );
		    Assert::IsTrue( unorderedSet.size() == 4 );
		    Assert::IsTrue( !unorderedSet.empty() );
		  }
			//erase
			//find
			//clear
			{
				UnorderedSet<int> unorderedSet;
				unorderedSet.insert( 5 );
				unorderedSet.insert( 3 );
				unorderedSet.insert( 9 );
				unorderedSet.insert( 1 );
        const auto ptr = unorderedSet.erase( 3 );
				const auto ptr2 = unorderedSet.find( 3 );
				Assert::IsTrue( ptr == nullptr && ptr2 == nullptr );
				unorderedSet.clear();
				Assert::IsTrue( unorderedSet.size() == 0 );
			}
			//T.Hash, T.operator==
			{
				UnorderedSet<Data, Data::Hash, Data::Equal> unorderedSet;
				unorderedSet.insert( Data{ 5 } );
				unorderedSet.insert( Data{ 3 } );
				unorderedSet.insert( Data{ 9 } );
				unorderedSet.insert( Data{ 1 } );
				const auto ptr = unorderedSet.erase( Data{ 3 }  );
				const auto ptr2 = unorderedSet.find( Data{ 3 }  );
				Assert::IsTrue( ptr == nullptr && ptr2 == nullptr );
				unorderedSet.clear();
				Assert::IsTrue( unorderedSet.size() == 0 );
			}
		}

		TEST_METHOD( Test_DoubleHashingProbing )
		{
			// DoubleHashingProbing
			//
			//insert
			//find
			//erase
			{
				HashTableWithOpenAddressing<int, std::string> unorderedSet;
				unorderedSet.insert( { 5, "" }  );
				unorderedSet.insert( { 3, "" }  );
				unorderedSet.insert( { 9, "" }  );
				unorderedSet.insert( { 1, "" }  );
				Assert::IsTrue( unorderedSet.find( 3 ) );
				Assert::IsFalse( unorderedSet.find( 2 ) );
				unorderedSet.erase( 3 );
				unorderedSet.erase( 1 );
				unorderedSet.erase( 9 );
				unorderedSet.erase( 5 );
			}
		}

		TEST_METHOD( Test_MyStack )
		{
			// push
			// pop
			// size
			// empty
			// emplace
			{
				Stack<int> stack;
				stack.push( 3 );
				stack.push( 5 );
				stack.push( 7 );
				stack.pop();
				Assert::IsTrue( stack.size() == 2 );
				stack.pop();
				stack.pop();
				Assert::IsTrue( stack.empty() );
				stack.push( 1 );
				stack.push( 3 );
				stack.push( 6 );
				auto value = stack.top();
				stack.pop();
				stack.push( 5 );
				stack.push( value );
				Assert::IsTrue( stack.top() == 6 );
				stack.emplace( 7 );
				Assert::IsTrue( stack.top() == 7 );
			}
		}
		TEST_METHOD( Test_MyQueue )
		{
			// push
			// pop
			// back
			// front
			// size
			// empty
			// emplace
			{
				Queue<int> queue;
				queue.push( 3 );
				queue.push( 5 );
				queue.push( 7 );
				queue.pop();
				Assert::IsTrue( queue.size() == 2 );
				queue.pop();
				queue.pop();
				Assert::IsTrue( queue.empty() );
				queue.push( 1 );
				queue.push( 2 );
				queue.push( 3 );
				auto value = queue.front();
				queue.pop();
				queue.push( 4 );
				queue.push( value );
				Assert::IsTrue( queue.back() == 1 );
				queue.emplace( 7 );
				Assert::IsTrue( queue.back() == 7 );
			}
		}
		TEST_METHOD( Test_MyPriorityQueue )
		{
			// push
			// emplace
			// top
			// pop
			// empty
			// size
			{
				PriorityQueue<int> priority_queue;
				priority_queue.emplace( 5 );
				priority_queue.push( 3 );
				priority_queue.emplace( 2 );
				priority_queue.push( 1 );
				priority_queue.push( 4 );
				priority_queue.push( 7 );
				Assert::IsTrue( priority_queue.top() == 7 );
				priority_queue.pop();
				Assert::IsTrue( priority_queue.top() == 5 );
				priority_queue.pop();
				Assert::IsTrue( priority_queue.top() == 4 );
				priority_queue.pop();
				Assert::IsTrue( priority_queue.top() == 3 );
				priority_queue.pop();
				Assert::IsTrue( priority_queue.top() == 2 );
				priority_queue.pop();
				Assert::IsTrue( priority_queue.top() == 1 );
				priority_queue.pop();
				Assert::IsTrue( priority_queue.empty() );
				Assert::IsTrue( priority_queue.size() == 0 );
				priority_queue.pop();
				Assert::IsTrue( priority_queue.empty() );
			}
		}
	};
}
