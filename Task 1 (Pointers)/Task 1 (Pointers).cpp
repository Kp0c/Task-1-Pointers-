#include "stdafx.h"

#include "Task 1 (Pointers).h"

using namespace std;

void printList(char** list) 
{
	int size = StringListSize(list);
	for (int i = 0; i < size; i++)
	{
		cout << i << ": " << list[i + 1] << endl;
	}
}

void printCapacity(char** list) 
{
	cout << "Capacity: " << StringListCapacity(list) << endl;
}

int main()
{
	//list[0] reserved for inner info, so your element located at list[x+1]
	char** myList = nullptr;
	StringListInit(&myList);

	for (int i = 0; i < 112; ++i)
	{
		char buff[4];
		StringListAdd(&myList, itoa(i, buff, 10));
	}

	//StringListRemoveElementAt(myList, 0);
	//cout << StringListIndexOf(myList, "5") << endl;
	//StringListRemove(myList, "5");

	/*StringListAdd(&myList, "5");
	StringListAdd(&myList, "6");
	StringListAdd(&myList, "6");
	StringListRemoveDuplicates(myList);*/

	//StringListRemoveElementAt(myList, StringListIndexOf(myList, "0"));

	//StringListReplaceInStrings(myList, "4", "3");

	//StringListSort(myList);

	printList(myList);
	StringListDestroy(&myList);
	return 0;
}