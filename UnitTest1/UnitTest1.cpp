#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\user\source\repos\ConsoleApplication3\ConsoleApplication3\ConsoleApplication3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestMethod_OddListCount)
		{
			std::vector<int> arr =
			{ 1, 3, 4, 7, 9, 12, 15 };

			auto operationSearch = 0;
			Assert::AreEqual(1, binary_search(arr, 3, operationSearch));
			Assert::AreEqual(2, operationSearch);

			operationSearch = 0;
			Assert::AreEqual(6, binary_search(arr, 15, operationSearch));
			Assert::AreEqual(3, operationSearch);

			operationSearch = 0;
			Assert::AreEqual(NOT_FOUND, binary_search(arr, -4, operationSearch));
			Assert::AreEqual(3, operationSearch);
		}

		TEST_METHOD(TestMethod_MiddleValue)
		{
			auto operationSearch = 0;
		  std::vector<int> arr =
			{ 1, 3, 4, 7, 9, 12, 15 };
		  Assert::AreEqual(3, binary_search(arr, 7, operationSearch));
			Assert::AreEqual(1, operationSearch);


			operationSearch = 0;
			std::vector<int> arr2 =
			{ 1, 3, 4, 7, 9, 12 };
			Assert::AreEqual(2, binary_search(arr2, 4, operationSearch));
			Assert::AreEqual(1, operationSearch);
		}

		TEST_METHOD(TestMethod_EvenListCount)
		{
			std::vector<int> arr =
			{ 1, 3, 4, 7, 9, 12 };

			auto operationSearch = 0;
		  Assert::AreEqual(1, binary_search(arr, 3, operationSearch));
		  Assert::AreEqual(3, operationSearch);

			operationSearch = 0;
		  Assert::AreEqual(4, binary_search(arr, 9, operationSearch));
		  Assert::AreEqual(2, operationSearch);

			operationSearch = 0;
		  Assert::AreEqual(NOT_FOUND, binary_search(arr, 13, operationSearch));
		  Assert::AreEqual(3, operationSearch);
		}
	};
}
