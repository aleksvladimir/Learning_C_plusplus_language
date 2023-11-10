
#include <algorithm>
#include <vector>

static unsigned int allocCounter = 0;

void * operator new( size_t size )
{
	allocCounter++;
	return malloc( size );
}

void operator delete( void * p ) noexcept
{
	if ( p )
	{
		allocCounter--;
	  free( p );
	}
}

#include "../../EducationLibs/SmartPointers/AutoPtr.h"
#include "../../EducationLibs/SmartPointers/SharedPtr.h"
#include "../../EducationLibs/SmartPointers/UniquePtr.h"
#include "../../EducationLibs/SmartPointers/WeakPtr.h"

#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SmartPointerTests
{
	TEST_CLASS(SmartPointerTests)
	{
	public:
		
		TEST_METHOD(Test_std_auto_ptr)
		{
			allocCounter = 0;
		  {
		    //default_ctr
		    std::auto_ptr<int> a_ptr( new int );
		    Assert::IsNotNull( a_ptr.get() );

		    //default_ctr
		    std::auto_ptr<int> a_ptr3;
		    //*a_ptr3 = 3;
		    Assert::IsNull( a_ptr3.get() );

		    //copy_ctr
		    auto a_ptr2( a_ptr );
		    Assert::IsNull( a_ptr.get() );

		    //*
		    *a_ptr2 = 2;
		    Assert::AreEqual( 2, *a_ptr2 );

		    //copy_operator
		    a_ptr3 = a_ptr2;
		    Assert::IsNull( a_ptr2.get() );

		    //reference
		    auto & a_ptr4 = a_ptr3;
		    Assert::IsNotNull( a_ptr3.get() );
		    *a_ptr4 = 4;
		    Assert::AreEqual( 4, *a_ptr3 );

		    // release
		    auto p = a_ptr3.release();
		    Assert::IsNull( a_ptr3.get() );
		    Assert::IsNotNull( p );

		    // reset
		    std::auto_ptr<int> resetObj( p );
		    resetObj.reset();
		    Assert::IsNull( resetObj.get() );
		    Assert::AreNotEqual( 4, *p );
		  }

			Assert::IsTrue( allocCounter == 0 );
		}

		TEST_METHOD(Test_MyAutoPtr)
		{
			allocCounter = 0;
			{
				//copy_operator
				AutoPtr<int> a_ptr1( new int );
				AutoPtr<int> a_ptr2( new int );
				Assert::IsTrue( allocCounter == 2 );
				a_ptr2 = a_ptr1;
				Assert::IsTrue( allocCounter == 1 );
				Assert::IsNull( a_ptr1.get() );
				Assert::IsNotNull( a_ptr2.get() );
			}
		  {
		    //default_ctr
		    AutoPtr<int> a_ptr( new int );
		    Assert::IsNotNull( a_ptr.get() );

		    //default_ctr
		    AutoPtr<int> a_ptr3;
		    //*a_ptr3 = 3;
		    Assert::IsNull( a_ptr3.get() );

		    //copy_ctr
		    auto a_ptr2( a_ptr );
		    Assert::IsNull( a_ptr.get() );

		    //*
		    *a_ptr2 = 2;
		    Assert::AreEqual( 2, *a_ptr2 );

		    //copy_operator
		    a_ptr3 = a_ptr2;
		    Assert::IsNull( a_ptr2.get() );

		    //reference
		    auto & a_ptr4 = a_ptr3;
		    Assert::IsNotNull( a_ptr3.get() );
		    *a_ptr4 = 4;
		    Assert::AreEqual( 4, *a_ptr3 );

		    // release
		    auto p = a_ptr3.release();
		    Assert::IsNull( a_ptr3.get() );
		    Assert::IsNotNull( p );

		    // reset
		    AutoPtr<int> resetObj( p );
		    resetObj.reset();
		    Assert::IsNull( resetObj.get() );
		    Assert::AreNotEqual( 4, *p );
		  }
			// protect from UB - new void
			{
				//AutoPtr<void> a_ptr( ( void * )new int );	// error compile!!! prohibition of instantiation
				//Assert::IsNotNull( a_ptr.get() );
			}
			// protect from UB - new int[]
			// deleter
			{
				AutoPtr<int[]> a_ptr( new int[ 100 ] );
				Assert::IsNotNull( a_ptr.get() );
			}
			Assert::IsTrue( allocCounter == 0 );
		}

		TEST_METHOD( Test_std_unique_ptr )
		{
			allocCounter = 0;
			{
				// move_operator
				std::unique_ptr<int> p1( new int );
				std::unique_ptr<int> p2( new int );
				p2 = std::move( p1 );
				Assert::IsNull( p1.get() );
			}
			Assert::IsTrue( allocCounter == 0 );

		  {
		    // default_ctr
			  std::unique_ptr<int> a_ptr0;
			  std::unique_ptr<int> a_ptr1( new int );
			  Assert::IsNull( a_ptr0.get() );
			  Assert::IsNotNull( a_ptr1.get() );

			  // move_ctr + get
			  auto a_ptr2( std::move( a_ptr1 ) );
			  Assert::IsNull( a_ptr1.get() );
			  //auto a_ptr2( a_ptr1 );	// compile error! copy_ctr is deleted!

			  // *
			  *a_ptr2 = 2;
			  Assert::AreEqual( 2, *a_ptr2 );

			  // move_operator
			  a_ptr0 = std::move(a_ptr2);	// same as "static_cast< std::unique_ptr<int> &&>(a_ptr2)"
			  //a_ptr0 = a_ptr2;				// compile error! copy_operator is deleted!
			  Assert::IsNull( a_ptr2.get() );

			  //reference
			  auto & a_ptr4 = a_ptr0;
			  Assert::IsNotNull( a_ptr0.get() );
			  *a_ptr4 = 4;
			  Assert::AreEqual( 4, *a_ptr0 );

			  // release
			  auto p = a_ptr0.release();
			  Assert::IsNull( a_ptr0.get() );
			  Assert::IsNotNull( p );

			  // reset
			  std::unique_ptr<int> resetObj( p );
			  resetObj.reset();
			  Assert::IsNull( resetObj.get() );
			  Assert::AreNotEqual( 4, *p );
		  }

			Assert::IsTrue( allocCounter == 0 );
		}

		TEST_METHOD( Test_MyUniquePtr )
		{
			allocCounter = 0;
			{
				// move_operator
				UniquePtr<int> p1( new int );
				UniquePtr<int> p2( new int );
				p2 = std::move( p1 );
				Assert::IsNull( p1.get() );
			}
			Assert::IsTrue( allocCounter == 0 );

		  {
		    // default_ctr
		    UniquePtr<int> a_ptr0;
		    UniquePtr<int> a_ptr1( new int );
		    Assert::IsNull( a_ptr0.get() );
		    Assert::IsNotNull( a_ptr1.get() );

		    // move_ctr + get
		    auto a_ptr2( std::move( a_ptr1 ) );
		    Assert::IsNull( a_ptr1.get() );
		    //auto a_ptr3( a_ptr1 );	// compile error! copy_ctr is deleted!

		    // *
		    *a_ptr2 = 2;
		    Assert::AreEqual( 2, *a_ptr2 );

		    // move_operator
		    a_ptr0 = std::move( a_ptr2 );
		    //a_ptr0 = a_ptr2;				// compile error! copy_operator is deleted!
		    Assert::IsNull( a_ptr2.get() );

		    //reference
		    auto & a_ptr4 = a_ptr0;
		    Assert::IsNotNull( a_ptr0.get() );
		    *a_ptr4 = 4;
		    Assert::AreEqual( 4, *a_ptr0 );

		    // release
		    auto p = a_ptr0.release();
		    Assert::IsNull( a_ptr0.get() );
		    Assert::IsNotNull( p );

		    // reset
		    UniquePtr<int> resetObj( p );
		    resetObj.reset();
		    Assert::IsNull( resetObj.get() );
		    Assert::AreNotEqual( 4, *p );
		  }
			// protect from UB - new void
			{
				//UniquePtr<void> a_ptr( ( void * )new int );	// error compile!!! prohibition of instantiation
				//Assert::IsNotNull( a_ptr.get() );
			}
			// protect from UB - new int[]
			// deleter
			{
				UniquePtr<int[]> a_ptr( new int[ 100 ] );
				Assert::IsNotNull( a_ptr.get() );
			}
			Assert::IsTrue( allocCounter == 0 );
		}

		TEST_METHOD( Test_std_shared_ptr )
		{
			allocCounter = 0;

			{
				// copy_operator
				std::shared_ptr<int> p2( new int( 22 ) );	// p2.c=1
				std::shared_ptr<int> p22( p2 );						// p2.c=2 p22.c=2 
				std::shared_ptr<int> p1( new int( 11 ) );	// p1.c=1
				Assert::IsTrue( allocCounter == 4 );
				Assert::AreEqual( 2, static_cast< int >( p22.use_count() ) );
				Assert::AreEqual( 1, static_cast< int >( p1.use_count() ) );
				p2 = p1;	// p22.c=1. p1.c=2 (p1 -> p2 -> 11)
				Assert::AreEqual( 1, static_cast< int >( p22.use_count() ) );
				Assert::AreEqual( 2, static_cast< int >( p1.use_count() ) );
				Assert::IsTrue( allocCounter == 4 );
			}
			Assert::IsTrue( allocCounter == 0 );

			{
				// copy_operator
				std::shared_ptr<int> ref2( new int( 22 ) );	// ref2.c=1
				std::shared_ptr<int> ref1( new int( 11 ) );	// ref1.c=1
				Assert::IsTrue( allocCounter == 4 );
				Assert::AreEqual( 1, static_cast< int >( ref2.use_count() ) );
				Assert::AreEqual( 1, static_cast< int >( ref1.use_count() ) );
				ref2 = ref1;	// ref1.c=2 ref2.c=2 (ref1 -> ref2 -> 11)
				Assert::AreEqual( 2, static_cast< int >( ref2.use_count() ) );
				Assert::AreEqual( 2, static_cast< int >( ref1.use_count() ) );
				Assert::IsTrue( allocCounter == 2 );
			}
			Assert::IsTrue( allocCounter == 0 );

			// default_ctr
			std::shared_ptr<int> a_ptr0;
			Assert::AreEqual( 0, static_cast< int >( a_ptr0.use_count() ) );
			Assert::IsNull( a_ptr0.get() );
			{
				// default_ctr
				std::shared_ptr<int> a_ptr1( new int( 1 ) );	// counter = 1
				Assert::AreEqual( 1, static_cast< int >( a_ptr1.use_count() ) );
				Assert::IsNotNull( a_ptr1.get() );

				// copy_ctr
				auto a_ptr2( a_ptr1 );												// counter = 2
				Assert::IsNotNull( a_ptr2.get() );
				Assert::AreEqual( 2, static_cast< int >( a_ptr1.use_count() ) );
				Assert::IsTrue( a_ptr1.use_count() == a_ptr2.use_count() );

				// copy_operator
				a_ptr0 = a_ptr2;															// counter = 3
				Assert::AreEqual( 3, static_cast< int >( a_ptr1.use_count() ) );
				std::vector<long> counters{ a_ptr0.use_count(), a_ptr1.use_count(), a_ptr2.use_count() };
				Assert::IsTrue( std::all_of( counters.begin(), counters.end(), []( long i ) { return i == 3; } ) );

				// move_ctr
				auto a_ptr3( std::move( a_ptr2 ) );						// counter = 3
				Assert::IsNull( a_ptr2.get() );
				Assert::IsNotNull( a_ptr3.get() );
				Assert::AreEqual( 0, static_cast< int >( a_ptr2.use_count() ) );
				Assert::AreEqual( 3, static_cast< int >( a_ptr1.use_count() ) );
				counters.clear();
				counters = { a_ptr0.use_count(), a_ptr1.use_count(), a_ptr3.use_count() };
				Assert::IsTrue( std::all_of( counters.begin(), counters.end(), []( long i ) { return i == 3; } ) );

				// move_operator
				a_ptr0 = std::move( a_ptr3 );									// counter = 2
				Assert::IsNull( a_ptr3.get() );
				Assert::AreEqual( 0, static_cast< int >( a_ptr3.use_count() ) );
				Assert::AreEqual( 2, static_cast< int >( a_ptr1.use_count() ) );
				Assert::IsTrue( a_ptr0.use_count() == a_ptr1.use_count() );

				// *
				*a_ptr0 = 2;
				Assert::AreEqual( 2, *a_ptr1 );

				//reference
				auto & a_ptr4 = a_ptr0;												// counter = 2
				Assert::IsNotNull( a_ptr0.get() );
				*a_ptr4 = 4;
				Assert::AreEqual( 4, *a_ptr0 );

				// reset
				std::shared_ptr<int> resetObj( a_ptr0 );			// counter = 3
				Assert::AreEqual( 3, static_cast< int >( a_ptr1.use_count() ) );
				resetObj.reset();															// counter = 2
				resetObj.reset();															// counter = 2
				Assert::IsNull( resetObj.get() );
				Assert::AreEqual( 0, static_cast< int >( resetObj.use_count() ) );
				Assert::AreEqual( 2, static_cast< int >( a_ptr1.use_count() ) );
				Assert::IsTrue( a_ptr0.use_count() == a_ptr1.use_count() );

			}																								// counter = 1
			Assert::AreEqual( 1, static_cast< int >( a_ptr0.use_count() ) );

			a_ptr0.reset();																	// counter = 0
			Assert::IsNull( a_ptr0.get() );
			Assert::AreEqual( 0, static_cast< int >( a_ptr0.use_count() ) );

			Assert::IsTrue( allocCounter == 0 );
		}

		TEST_METHOD( Test_MySharedPtr )
		{
			allocCounter = 0;
		  {
		    {
		      // default_ctr
		      SharedPtr<int> a_ptr0;
		      Assert::IsTrue( allocCounter == 1 );
		    }
			  Assert::IsTrue( allocCounter == 0 );

			  {
		      // default_ctr
		      SharedPtr<int> a_ptr0( new int( 1 ) );
		      Assert::IsTrue( allocCounter == 2 );
			  }
			  Assert::IsTrue( allocCounter == 0 );

			  {
		      // default_ctr
		      SharedPtr<int> a_ptr0( new int( 1 ) );
					Assert::AreEqual( 1, static_cast< int >( a_ptr0.use_count() ) );
					Assert::IsNotNull( a_ptr0.get() );
					// copy_ctr
		      SharedPtr<int> a_ptr1( a_ptr0 );
		      Assert::IsTrue( allocCounter == 2 );
			  }
			  Assert::IsTrue( allocCounter == 0 );

				{
					// copy_operator
					SharedPtr<int> ref2( new int( 22 ) );	// ref2.c=1
					SharedPtr<int> ref22( ref2 );					// ref2.c=2 ref22.c=2 
					SharedPtr<int> ref1( new int( 11 ) );	// ref1.c=1
					Assert::IsTrue( allocCounter == 4 );
					Assert::AreEqual( 2, static_cast< int >( ref22.use_count() ) );
					Assert::AreEqual( 1, static_cast< int >( ref1.use_count() ) );
					ref2 = ref1;	// ref22.c=1. ref1.c=2 (ref1 -> ref2 -> 11)
					Assert::AreEqual( 1, static_cast< int >( ref22.use_count() ) );
					Assert::AreEqual( 2, static_cast< int >( ref1.use_count() ) );
					Assert::IsTrue( allocCounter == 4 );
				}
				Assert::IsTrue( allocCounter == 0 );

				{
					// copy_operator
					SharedPtr<int> ref2( new int( 22 ) );	// ref2.c=1
					SharedPtr<int> ref1( new int( 11 ) );	// ref1.c=1
					Assert::IsTrue( allocCounter == 4 );
					Assert::AreEqual( 1, static_cast< int >( ref2.use_count() ) );
					Assert::AreEqual( 1, static_cast< int >( ref1.use_count() ) );
					ref2 = ref1;	// ref1.c=2 ref2.c=2 (ref1 -> ref2 -> 11)
					Assert::AreEqual( 2, static_cast< int >( ref2.use_count() ) );
					Assert::AreEqual( 2, static_cast< int >( ref1.use_count() ) );
					Assert::IsTrue( allocCounter == 2 );
				}
				Assert::IsTrue( allocCounter == 0 );


				{
					// move_operator
					SharedPtr<int> p2( new int( 22 ) );
					SharedPtr<int> p22( p2 );
					SharedPtr<int> p1( new int( 11 ) );
					Assert::IsTrue( allocCounter == 4 );
					p2 = std::move( p1 );
					Assert::IsTrue( allocCounter == 4 );
				}
				Assert::IsTrue( allocCounter == 0 );

			  // default_ctr
			  SharedPtr<int> a_ptr0;
			  Assert::AreEqual( 0, static_cast< int >( a_ptr0.use_count() ) );
			  Assert::IsNull( a_ptr0.get() );
			  {
		      // default_ctr
		      SharedPtr<int> a_ptr1( new int( 1 ) );				// counter = 1
		      Assert::AreEqual( 1, static_cast< int >( a_ptr1.use_count() ) );
		      Assert::IsNotNull( a_ptr1.get() );

		      // copy_ctr
		      auto a_ptr2( a_ptr1 );												// counter = 2
		      Assert::IsNotNull( a_ptr2.get() );
		      Assert::AreEqual( 2, static_cast< int >( a_ptr1.use_count() ) );
		      Assert::IsTrue( a_ptr1.use_count() == a_ptr2.use_count() );

		      // copy_operator
		      a_ptr0 = a_ptr2;															// counter = 3
		      Assert::AreEqual( 3, static_cast< int >( a_ptr1.use_count() ) );
		      std::vector<long> counters{ a_ptr0.use_count(), a_ptr1.use_count(), a_ptr2.use_count() };
		      Assert::IsTrue( std::all_of( counters.begin(), counters.end(), []( long i ) { return i == 3; } ) );

		      // move_ctr
		      auto a_ptr3( std::move( a_ptr2 ) );						// counter = 3
		      Assert::IsNull( a_ptr2.get() );
		      Assert::IsNotNull( a_ptr3.get() );
		      Assert::AreEqual( 0, static_cast< int >( a_ptr2.use_count() ) );
		      Assert::AreEqual( 3, static_cast< int >( a_ptr1.use_count() ) );
		      counters.clear();
		      counters = { a_ptr0.use_count(), a_ptr1.use_count(), a_ptr3.use_count() };
		      Assert::IsTrue( std::all_of( counters.begin(), counters.end(), []( long i ) { return i == 3; } ) );

		      // move_operator
		      a_ptr0 = std::move( a_ptr3 );									// counter = 2
		      Assert::IsNull( a_ptr3.get() );
		      Assert::AreEqual( 0, static_cast< int >( a_ptr3.use_count() ) );
		      Assert::AreEqual( 2, static_cast< int >( a_ptr1.use_count() ) );
		      Assert::IsTrue( a_ptr0.use_count() == a_ptr1.use_count() );

		      // *
		      *a_ptr0 = 2;
		      Assert::AreEqual( 2, *a_ptr1 );

		      //reference
		      auto & a_ptr4 = a_ptr0;												// counter = 2
		      Assert::IsNotNull( a_ptr0.get() );
		      *a_ptr4 = 4;
		      Assert::AreEqual( 4, *a_ptr0 );

		      // reset
		      SharedPtr<int> resetObj( a_ptr0 );						// counter = 3
		      Assert::AreEqual( 3, static_cast< int >( a_ptr1.use_count() ) );
		      resetObj.reset();															// counter = 2
		      resetObj.reset();															// counter = 2
		      Assert::IsNull( resetObj.get() );
		      Assert::AreEqual( 0, static_cast< int >( resetObj.use_count() ) );
		      Assert::AreEqual( 2, static_cast< int >( a_ptr1.use_count() ) );
		      Assert::IsTrue( a_ptr0.use_count() == a_ptr1.use_count() );

			  }																								// counter = 1
			  Assert::AreEqual( 1, static_cast< int >( a_ptr0.use_count() ) );

			  a_ptr0.reset();																	// counter = 0
			  Assert::IsNull( a_ptr0.get() );
			  Assert::AreEqual( 0, static_cast< int >( a_ptr0.use_count() ) );
		  }
			// protect from UB - new void
			{
			  //SharedPtr<void> a_ptr( ( void * )new int );	// error compile!!! prohibition of instantiation
			  //Assert::IsNotNull( a_ptr.get() );
			}
			// protect from UB - new int[]
			// deleter
			{
				SharedPtr<int[]> a_ptr( new int[100] );
				Assert::IsNotNull( a_ptr.get() );
			}

			Assert::IsTrue( allocCounter == 0 );
		}

		TEST_METHOD( Test_std_weak_ptr )
		{
			allocCounter = 0;
		  {
		    // default_ctr nullptr
		    std::weak_ptr<int> a_ptr0;
		    Assert::AreEqual( 0, static_cast< int >( a_ptr0.use_count() ) );
		    Assert::IsTrue( a_ptr0.expired() );
		  }
			{
				// copy_ctr weak-weak
				std::weak_ptr<int> a_ptr0;
				std::weak_ptr<int> a_ptr1( a_ptr0 );
				Assert::AreEqual( 0, static_cast< int >( a_ptr1.use_count() ) );
				Assert::IsTrue( a_ptr1.expired() );
			}
			{
				// copy_ctr weak r-value shared_ptr
				std::weak_ptr<int> a_ptr1( std::shared_ptr<int>( new int( 2 ) ) );
				Assert::AreEqual( 0, static_cast< int >( a_ptr1.use_count() ) );
				Assert::IsTrue( a_ptr1.expired() );
			}
			{
				// copy_ctr weak-weak r-value shared_ptr
				std::weak_ptr<int> a_ptr1( std::shared_ptr<int>( new int( 2 ) ) );
				auto a_ptr2( a_ptr1 );
				Assert::IsTrue( a_ptr2.expired() );
				Assert::AreEqual( 0, static_cast< int >( a_ptr1.use_count() ) );
				Assert::IsTrue( a_ptr1.use_count() == a_ptr2.use_count() );
			}
			{
				// copy_ctr weak-shared
				std::shared_ptr<int> a_ptr0( new int( 4 ) );
				std::weak_ptr<int> a_ptr1( a_ptr0 );
				std::weak_ptr<int> a_ptr2( a_ptr1 );
				Assert::AreEqual( 1, static_cast< int >( a_ptr0.use_count() ) );
				Assert::AreEqual( 1, static_cast< int >( a_ptr1.use_count() ) );
				Assert::AreEqual( 1, static_cast< int >( a_ptr2.use_count() ) );
				Assert::IsTrue( !a_ptr1.expired() );
				Assert::IsTrue( !a_ptr2.expired() );
			}
			{
				// copy_operator weak-weak
				std::weak_ptr<int> a_ptr0;
				std::weak_ptr<int> a_ptr1;
				a_ptr0 = a_ptr1;
			}
			{
				// copy_operator weak-shared
				std::weak_ptr<int> a_ptr0;
				std::shared_ptr<int> a_ptr1( new int( 4 ) );
				a_ptr0 = a_ptr1;
				Assert::IsTrue( !a_ptr0.expired() );
			}
			{
				// move_ctr
				std::weak_ptr<int> a_ptr0;
				auto a_ptr1( std::move( a_ptr0 ) );
			}
			{
				// move_operator
				std::weak_ptr<int> a_ptr0;
				std::weak_ptr<int> a_ptr1;
				a_ptr1 = std::move( a_ptr0 );
			}
			{
				//reference
				std::weak_ptr<int> a_ptr0;
				auto & a_ptr8 = a_ptr0;
			}
			{
				// expired
				std::shared_ptr<int> a_ptr0( new int( 4 ) );
				std::weak_ptr<int> a_ptr1( a_ptr0 );
				Assert::IsTrue( !a_ptr1.expired() );
			}
			{
				// reset
				std::shared_ptr<int> a_ptr0( new int( 4 ) );
				auto a_ptr1( a_ptr0 );
				auto a_ptr2( a_ptr1 );	// Use_ == 3
				Assert::AreEqual( 3, static_cast< int >( a_ptr0.use_count() ) );
				std::weak_ptr<int> a_ptrW0( a_ptr0 );
				auto a_ptrW1( a_ptrW0 );
				auto a_ptrW2( a_ptrW1 );
				auto a_ptrW3( a_ptrW2 );
				auto a_ptrW4( a_ptrW3 );
				Assert::IsTrue( !a_ptrW0.expired() );
				a_ptrW0.reset();
				Assert::IsTrue( a_ptrW0.expired() );
				a_ptrW0.reset();
				a_ptrW0.reset();
				Assert::AreEqual( 3, static_cast< int >( a_ptr0.use_count() ) );
				Assert::AreEqual( 0, static_cast< int >( a_ptrW0.use_count() ) );
				Assert::AreEqual( 3, static_cast< int >( a_ptrW1.use_count() ) );
				Assert::IsTrue( !a_ptrW1.expired() );
			}
			{
				// lock empty weak_ptr r-value shared_ptr
				std::weak_ptr<int> a_ptr0( std::shared_ptr<int>( new int( 4 ) ) );
				auto a_ptr1 = a_ptr0.lock();
				Assert::IsTrue( a_ptr0.expired() );	// from empty weak_ptr (Use_ == 0) we cant create shared_ptr
			}
			{
				// lock not empty weak_ptr:
				//	copy-ctr shared_ptr from not empty weak_ptr
				std::shared_ptr<int> a_ptr0( new int( 4 ) );
				auto a_ptr1( a_ptr0 );
				Assert::AreEqual( 2, static_cast< int >( a_ptr0.use_count() ) );
				a_ptr0.reset();
				Assert::IsNull( a_ptr0.get() );
				Assert::AreEqual( 0, static_cast< int >( a_ptr0.use_count() ) );
				Assert::AreEqual( 1, static_cast< int >( a_ptr1.use_count() ) );
				std::weak_ptr<int> a_ptr2( a_ptr1 );
				a_ptr0 = a_ptr2.lock();
				Assert::AreEqual( 2, static_cast< int >( a_ptr0.use_count() ) );
				Assert::AreEqual( 2, static_cast< int >( a_ptr1.use_count() ) );
			}

			Assert::IsTrue( allocCounter == 0 );
		}

		TEST_METHOD( Test_WeakPtr )
		{
			{
				// default_ctr nullptr
				WeakPtr<int> a_ptr0;
				Assert::AreEqual( 0, static_cast< int >( a_ptr0.use_count() ) );
				Assert::IsTrue( a_ptr0.expired() );
			}
			{
				// copy_ctr weak-weak
				WeakPtr<int> a_ptr0;
				WeakPtr<int> a_ptr1( a_ptr0 );
				Assert::AreEqual( 0, static_cast< int >( a_ptr1.use_count() ) );
				Assert::IsTrue( a_ptr1.expired() );
			}
			{
				// copy_ctr weak r-value shared_ptr
				WeakPtr<int> a_ptr1( SharedPtr<int>( new int( 2 ) ) );
				Assert::AreEqual( 0, static_cast< int >( a_ptr1.use_count() ) );
				Assert::IsTrue( a_ptr1.expired() );
			}
			{
				// copy_ctr weak-weak r-value shared_ptr
				WeakPtr<int> a_ptr1( SharedPtr<int>( new int( 2 ) ) );
				auto a_ptr2( a_ptr1 );
				Assert::IsTrue( a_ptr2.expired() );
				Assert::AreEqual( 0, static_cast< int >( a_ptr1.use_count() ) );
				Assert::IsTrue( a_ptr1.use_count() == a_ptr2.use_count() );
			}
			{
				// copy_ctr weak-shared
				SharedPtr<int> a_ptr0( new int( 4 ) );
				WeakPtr<int> a_ptr1( a_ptr0 );
				WeakPtr<int> a_ptr2( a_ptr1 );
				Assert::AreEqual( 1, static_cast< int >( a_ptr0.use_count() ) );
				Assert::AreEqual( 1, static_cast< int >( a_ptr1.use_count() ) );
				Assert::AreEqual( 1, static_cast< int >( a_ptr2.use_count() ) );
				Assert::IsTrue( !a_ptr1.expired() );
				Assert::IsTrue( !a_ptr2.expired() );
			}
			{
				// copy_operator weak-weak
				WeakPtr<int> a_ptr0;
				WeakPtr<int> a_ptr1;
				a_ptr0 = a_ptr1;
			}
			{
				// copy_operator weak-shared
				WeakPtr<int> a_ptr0;
				SharedPtr<int> a_ptr1( new int( 4 ) );
				a_ptr0 = a_ptr1;
				Assert::IsTrue( !a_ptr0.expired() );
			}
			{
				// move_ctr
				WeakPtr<int> a_ptr0;
				auto a_ptr1( std::move( a_ptr0 ) );
			}
			{
				// move_operator
				WeakPtr<int> a_ptr0;
				WeakPtr<int> a_ptr1;
				a_ptr1 = std::move( a_ptr0 );
			}
			{
				//reference
				WeakPtr<int> a_ptr0;
				auto & a_ptr8 = a_ptr0;
			}
			{
				// expired
				SharedPtr<int> a_ptr0( new int( 4 ) );
				WeakPtr<int> a_ptr1( a_ptr0 );
				Assert::IsTrue( !a_ptr1.expired() );
			}
			{
				// reset
				SharedPtr<int> a_ptr0( new int( 4 ) );
				auto a_ptr1( a_ptr0 );
				auto a_ptr2( a_ptr1 );	// Use_ == 3
				Assert::AreEqual( 3, static_cast< int >( a_ptr0.use_count() ) );
				WeakPtr<int> a_ptrW0( a_ptr0 );
				auto a_ptrW1( a_ptrW0 );
				auto a_ptrW2( a_ptrW1 );
				auto a_ptrW3( a_ptrW2 );
				auto a_ptrW4( a_ptrW3 );
				Assert::IsTrue( !a_ptrW0.expired() );
				a_ptrW0.reset();
				Assert::IsTrue( a_ptrW0.expired() );
				a_ptrW0.reset();
				a_ptrW0.reset();
				Assert::AreEqual( 3, static_cast< int >( a_ptr0.use_count() ) );
				Assert::AreEqual( 0, static_cast< int >( a_ptrW0.use_count() ) );
				Assert::AreEqual( 3, static_cast< int >( a_ptrW1.use_count() ) );
				Assert::IsTrue( !a_ptrW1.expired() );
			}
			{
				// lock empty weak_ptr r-value shared_ptr
				WeakPtr<int> a_ptr0( SharedPtr<int>( new int( 4 ) ) );
				auto a_ptr1 = a_ptr0.lock();
				Assert::IsTrue( a_ptr0.expired() );	// from empty weak_ptr (Use_ == 0) we cant create shared_ptr
			}
			{
				// lock not empty weak_ptr:
				//	copy-ctr shared_ptr from not empty weak_ptr
				SharedPtr<int> a_ptr0( new int( 4 ) );
				auto a_ptr1( a_ptr0 );
				Assert::AreEqual( 2, static_cast< int >( a_ptr0.use_count() ) );
				a_ptr0.reset();
				Assert::IsNull( a_ptr0.get() );
				Assert::AreEqual( 0, static_cast< int >( a_ptr0.use_count() ) );
				Assert::AreEqual( 1, static_cast< int >( a_ptr1.use_count() ) );
				WeakPtr<int> a_ptr2( a_ptr1 );
				a_ptr0 = a_ptr2.lock();
				Assert::AreEqual( 2, static_cast< int >( a_ptr0.use_count() ) );
				Assert::AreEqual( 2, static_cast< int >( a_ptr1.use_count() ) );
			}

			Assert::IsTrue( allocCounter == 0 );
		}

	};
}
