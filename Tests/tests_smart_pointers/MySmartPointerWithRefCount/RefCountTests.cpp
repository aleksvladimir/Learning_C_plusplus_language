#include "../../../EducationLibs/SmartPointers/MySmartPointersWithRefCount/IRefCount.h"
#include "../../../EducationLibs/SmartPointers/MySmartPointersWithRefCount/RefCount.h"
#include "../../../EducationLibs/SmartPointers/MySmartPointersWithRefCount/RefCountPointer.h"

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SmartPointerTests
{
	TEST_CLASS( RefCountTests )
	{
	public:

		TEST_METHOD( Test_RefCount )
		{
      struct RefCountMock : RefCount { unsigned long use_count() const { return count; } };
			{
				// default_ctr nullptr
				RefCountMock* refCount = new RefCountMock;
				Assert::AreEqual( 0, static_cast< int >( refCount->use_count() ) );
				refCount->Grab();
				Assert::AreEqual( 1, static_cast< int >( refCount->use_count() ) );
				refCount->Release();
			}
			{
				// default_ctr nullptr
        RefCountPointer<RefCountMock> cpRefCount( new RefCountMock );
        Assert::AreEqual( 1, static_cast< int >( cpRefCount->use_count() ) );
				auto cp2 = cpRefCount;
				auto cp3( cpRefCount );
				RefCountPointer<RefCountMock> cp4( new RefCountMock );
				cp4 = cpRefCount;
				Assert::AreEqual( 4, static_cast< int >( cpRefCount->use_count() ) );
			}

			struct IRefCountMock : IRefCount {
			  unsigned long use_count() const { return count; }
				static RefCountPointer<IRefCountMock> make() { return RefCountPointer<IRefCountMock>( new IRefCountMock() ); }
			};
			{
				// IRefCount rfc; // now user can't create IRefCount without RefCountPointer
        RefCountPointer<IRefCountMock> cpRefCount( IRefCountMock::make() );
        Assert::AreEqual( 1, static_cast< int >( cpRefCount->use_count() ) );
			}
		}
	};
}
