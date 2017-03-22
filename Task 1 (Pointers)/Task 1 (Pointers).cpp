#include "stdafx.h"

#include "Task 1 (Pointers).h"

#include "List.h"
#include <iostream>

using namespace std;

void printList(char** list) {
	for (int i = 0; i < StringListSize(list); i++)
	{
		std::cout << i+1 << ": " << list[i] << endl;
	}
}

void printCapacity(char** list) {
	cout << "Capacity: " << (int)StringListCapacity(list) << endl;
}

//ENDTODO

int main()
{
	char** myList;
	StringListInit(&myList);
	///////////////////////////////////////////////////
	for (int i = 0; i < 10; i++)
	{
		StringListAdd(myList, "Hello");
	}

	printList(myList);
	printCapacity(myList);
	////////////////////////////////////////////////
	StringListDestroy(&myList);
    return 0;
}