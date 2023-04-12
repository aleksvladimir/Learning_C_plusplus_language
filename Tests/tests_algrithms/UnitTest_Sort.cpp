#include "CppUnitTest.h"
#include "../../EducationLibs/Algorithms/sort.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_Sort
{
	TEST_CLASS(UnitTest_Sort)
	{
	public:

		TEST_METHOD(TestMethod_OddListCount)
		{
			Assert::IsTrue(std::list<int>{ 1, 3, 4, 7, 9, 12, 15 } == sort({ 15, 3, 9, 4, 7, 1, 12 }));
		}

	};
}
