#include <iostream>
#include <LinkedList.h>

int main()
{


	LinkedList<int> myList;

	myList.pushFront(10);
	myList.pushFront(20);
	myList.popFront();
	myList.pushFront(30);
	myList.pushFront(40);
	myList.pushFront(40);


	for (auto iter = myList.begin(); iter != myList.end(); iter++) {
		std::cout << (*iter) << std::endl;
	}

	std::cout << std::endl;

	std::cout << "Now we insert 32 before the first fourty in the list." << std::endl;
	std::cout << std::endl;

	auto iter = myList.FindFirstValue(40);
	myList.insert(iter, 32);

	for (auto iter = myList.begin(); iter != myList.end(); iter++) {
		std::cout << (*iter) << std::endl;
	}
	std::cout << std::endl;

	for (auto iter = myList.begin(); iter != myList.end(); iter++) {
		std::cout << (*iter) << std::endl;
	}

	for (auto iter = myList.last(); iter != myList.end();)
	{
		iter = myList.erase(iter);
	}

	for (auto iter = myList.begin(); iter != myList.end(); iter++) {
		std::cout << (*iter) << std::endl;
		std::cout << std::endl;
	}

	std::cout << std::endl;

	myList.pushBack(10);
	myList.pushFront(5);
	myList.pushBack(20);
	myList.pushBack(15);
	myList.pushBack(30);

	for (auto iter = myList.begin(); iter != myList.end(); iter++) {
		std::cout << (*iter) << std::endl;
	}

	std::cout << std::endl;

	myList.remove(15);

	for (auto iter = myList.begin(); iter != myList.end(); iter++) {
		std::cout << (*iter) << std::endl;
	}

	std::cout << std::endl;

	myList.pushBack(70);
	myList.pushFront(65);
	myList.pushBack(29);
	myList.pushBack(85);
	myList.pushBack(60);

	for (auto iter = myList.begin(); iter != myList.end(); iter++) {
		std::cout << (*iter) << std::endl;
	}

	std::cout << std::endl;

	for (auto iter = myList.begin(); iter != myList.end(); iter++) {
		std::cout << (*iter) << std::endl;
	}

	std::cout << std::endl;

	system("pause");
	return EXIT_SUCCESS;
}
