#include "stdafx.h"

#include "Task_1_Pointers.h"

using namespace std;

void printList(char** list) 
{
	int size = StringListSize(list);
	for (int i = 0; i < size; i++)
	{
		cout << i << ": " << list[i] << endl;
	}

	if (size == 0)
	{
		cout << "list empty" << endl;
	}
	cout << "Size: " << StringListSize(list) << endl
		<< "Capacity: " << StringListCapacity(list) << endl;
}

void printCapacity(char** list) 
{
	cout << "Capacity: " << StringListCapacity(list) << endl;
}

int main()
{
	char** myList = nullptr;
	StringListInit(&myList);

	for (int i = 0; i < 100; ++i)
	{
		//char buff[4];
		//StringListAdd(&myList, itoa(i, buff, 10));
		StringListAdd(&myList, "5");
	}

	StringListRemoveDuplicates(myList);

	/*StringListRemoveElementAt(myList, 0);
	cout << StringListIndexOf(myList, "5") << endl;
	StringListRemove(myList, "5");

	StringListAdd(&myList, "5");
	StringListAdd(&myList, "6");
	StringListAdd(&myList, "6");
	StringListRemoveDuplicates(myList);

	StringListRemoveElementAt(myList, StringListIndexOf(myList, "0"));*/

	/*StringListAdd(&myList, "4");
	StringListAdd(&myList, "4");
	StringListAdd(&myList, "4");
	StringListAdd(&myList, "4");
	StringListReplaceInStrings(myList, "4", "3");*/

	//StringListSort(myList);

	printList(myList);
	StringListDestroy(&myList);
	return 0;
}