#include "stdafx.h"

#include "Task 1 (Pointers).h"

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

	StringListAdd(&myList, "abcd");
	StringListAdd(&myList, "abcc");
	StringListAdd(&myList, "ac");
	StringListAdd(&myList, "ab");
	StringListAdd(&myList, "ab");
	StringListAdd(&myList, "abcsadfc");
	StringListAdd(&myList, "acgfh");
	StringListAdd(&myList, "abvbn");
	StringListAdd(&myList, "abcvbn");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abawed");
	StringListAdd(&myList, "abaweqwed");
	StringListAdd(&myList, "abawedew");
	StringListAdd(&myList, "abawqweed");
	
	//StringListRemove(myList, "abawed");
	StringListRemoveDuplicates(myList);

	printList(myList);
	printCapacity(myList);

	StringListSort(myList);


	StringListReplaceInStrings(myList, "ab", "absdsd");

	printList(myList);
	printCapacity(myList);

	StringListDestroy(&myList);
    return 0;
}