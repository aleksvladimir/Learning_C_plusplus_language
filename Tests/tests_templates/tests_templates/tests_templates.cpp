#include "../../../EducationLibs/Templates/Templates/Singleton.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace teststemplates
{
	TEST_CLASS(teststemplates)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
      auto & fm = FileManager::getInstance();
      FileManager ss;
      auto & fm2 = ss.getInstance();
			Assert::IsTrue( &fm.val == &fm2.val );
		}
	};
}
