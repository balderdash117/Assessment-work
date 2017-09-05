#include "CppUnitTest.h"
#include "LinkedList.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CustomContainersTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(checkPushBack)
		{
			LinkedList<int> list;
			
			for (int count = 0 ; count < 10 ; ++count)
			{
				list.pushBack(count);
			}

			Assert::AreEqual(10u, list.getSize(), L"there should be 10 items in the list");
		}

		TEST_METHOD(checkPopBack)
		{
			LinkedList<int> list;

			for (int count = 0; count < 10; ++count)
			{
				list.pushBack(count);
			}

			for (int counter = 0; counter < 10; ++counter)
			{
				list.popBack();
			}

			Assert::AreEqual(0u, list.getSize(), L"there should be 0 items in the list");
		}

		TEST_METHOD(checkPushFront)
		{
			LinkedList<int> list;

			for (int count = 0; count < 10; ++count)
			{
				list.pushFront(count);
			}

			Assert::AreEqual(10u, list.getSize(), L"there should be 10 items in the list");
		}

		TEST_METHOD(checkPopFront)
		{
			LinkedList<int> list;

			for (int count = 0; count < 10; ++count)
			{
				list.pushFront(count);
			}

			Assert::AreEqual(10u, list.getSize(), L"there should be 0 items in the list");

			for (int counter = 0; counter < 10; ++counter)
			{
				list.popFront();
			}

			Assert::AreEqual(0u, list.getSize(), L"there should be 0 items in the list");
		}

		TEST_METHOD(Insertion)
		{
			LinkedList<int> list;
			list.pushBack(10);
			list.pushBack(20);
			// value should be inserted here
			list.pushBack(30);
			list.pushBack(40);
			list.pushBack(50);

			unsigned int initialSize = list.getSize();

			int index = 0;
			LinkedList<int>::LinkIterator iter;
			for (iter = list.begin(); iter != list.end(); iter++, index++)
			{
				if (index != 2)
					continue;

				list.insert(iter, 25);
				break;
			}

			// ensure the collection has increased in size
			Assert::AreEqual(initialSize + 1u, list.getSize(), L"there should be an additional item in this list");

			// ensure the node was inserted with the correct value
			--iter;
			Assert::AreEqual(25, (*iter), L"Expected the correct value to be inserted to the left");


			list.popBack();
			list.popBack();
			list.popBack();
			list.popBack();
			list.popBack();
			list.popBack();

			Assert::AreEqual(0u, list.getSize(), L"The list should be empty");

			list.pushBack(10);
			list.insert(list.begin(), 5);
			list.pushBack(20);
			list.pushBack(30);
			list.pushBack(40);
			list.pushBack(50);
			list.insert(list.end(), 45);

			int count = 1;

			for (iter = list.begin(); iter != list.end(); iter++ , count++)
			{
				switch (count)
				{
				case 1:
					Assert::AreEqual(5, (*iter), L"The value should be 5");
					break;
				case 2:
					Assert::AreEqual(10, (*iter), L"The value should be 10");
					break;
				case 3:
					Assert::AreEqual(20, (*iter), L"The value should be 20");
					break;
				case 4:
					Assert::AreEqual(30, (*iter), L"The value should be 30");
					break;
				case 5:
					Assert::AreEqual(40, (*iter), L"The value should be 40");
					break;
				case 6:
					Assert::AreEqual(50, (*iter), L"The value should be 50");
					break;
				case 7:
					Assert::AreEqual(45, (*iter), L"The value should be 45");
					break;
				}
			}
		}

		TEST_METHOD(findFirstValue)
		{
			LinkedList<int> list;

			for (int count = 0; count < 10; ++count)
			{
				list.pushFront(count);
			}

			auto iter = list.FindFirstValue(5);

			Assert::AreEqual(5, (*iter), L"It is not the correct value");

			auto iterator = list.FindFirstValue(12);

			bool check;

			if (iterator == nullptr)
			{
				check = true;
			}
			else
			{
				check = false;
			}

			Assert::IsTrue(check, L"This doesnt work when you check a value thats not in the list");
		}

		TEST_METHOD(eraseValues)
		{
			LinkedList<int> list;

			for (int count = 0; count < 10; ++count)
			{
				list.pushFront(count);
			}

			Assert::AreEqual(10u, list.getSize(), L"there should be 10 items in the list");

			for (auto iter = list.begin(); iter != list.end();)
			{
				iter = list.erase(iter);
			}

			Assert::AreEqual(0u, list.getSize(), L"there should be 0 items in the list");

			for (int count = 0; count < 10; ++count)
			{
				list.pushFront(count);
			}

			Assert::AreEqual(10u, list.getSize(), L"there should be 10 items in the list");

			for (auto iter = list.last(); iter != list.end();)
			{
				iter = list.erase(iter);
			}

			Assert::AreEqual(0u, list.getSize(), L"there should be 0 items in the list");

			for (int count = 0; count < 10; ++count)
			{
				list.pushBack(count);
			}

			Assert::AreEqual(10u, list.getSize(), L"there should be 10 items in the list");

			list.erase(list.begin());

			Assert::AreEqual(9u, list.getSize(), L"there should be 9 items in the list");
		}

		TEST_METHOD(removeItemFromList)
		{
			LinkedList<int> list;

			list.pushBack(10);
			list.pushFront(5);
			list.pushBack(20);
			list.pushBack(15);
			list.pushBack(30);

			int count = 1;

			for (auto iter = list.begin(); iter != list.end(); iter++, count++)
			{
				switch (count)
				{
				case 1:
					Assert::AreEqual(5, (*iter), L"The value should be 5");
					break;
				case 2:
					Assert::AreEqual(10, (*iter), L"The value should be 10");
					break;
				case 3:
					Assert::AreEqual(20, (*iter), L"The value should be 20");
					break;
				case 4:
					Assert::AreEqual(15, (*iter), L"The value should be 15");
					break;
				case 5:
					Assert::AreEqual(30, (*iter), L"The value should be 30");
					break;
				}
			}

			count = 1;

			list.remove(15);

			for (auto iter = list.begin(); iter != list.end(); iter++, count++)
			{
				switch (count)
				{
				case 1:
					Assert::AreEqual(5, (*iter), L"The value should be 5");
					break;
				case 2:
					Assert::AreEqual(10, (*iter), L"The value should be 10");
					break;
				case 3:
					Assert::AreEqual(20, (*iter), L"The value should be 20");
					break;
				case 4:
					Assert::AreEqual(30, (*iter), L"The value should be 30");
					break;
				}
			}

			count = 1;

			list.remove(5);
			list.remove(30);

			for (auto iter = list.begin(); iter != list.end(); iter++, count++)
			{
				switch (count)
				{
				case 1:
					Assert::AreEqual(10, (*iter), L"The value should be 10");
					break;
				case 2:
					Assert::AreEqual(20, (*iter), L"The value should be 20");
					break;
				}
			}

			list.remove(10);
			list.remove(20);

			Assert::AreEqual(0u, list.getSize(), L"there should be 0 items in the list");
		}
	};
}