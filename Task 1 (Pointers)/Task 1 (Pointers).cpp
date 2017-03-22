#include "stdafx.h"

#include "Task 1 (Pointers).h"

#include "List.h"
#include <iostream>

using namespace std;

void printList(char** list) {
	for (int i = 0; i < StringListSize(list); i++)
	{
		cout << i+1 << ": " << list[i] << endl;
	}
}

void printCapacity(char** list) {
	cout << "Capacity: " << (int)StringListCapacity(list) << endl;
}

int main()
{
	char** myList;
	StringListInit(&myList);

	StringListAdd(myList, "qqwe");
	StringListAdd(myList, "qqweqwe");
	StringListAdd(myList, "qqqwewe");
	StringListAdd(myList, "qwe");

	StringListRemove(myList, "qqweqwe");

	cout << myList[StringListIndexOf(myList, "qwe")] << endl;

	printList(myList);
	printCapacity(myList);

	StringListDestroy(&myList);
    return 0;
}