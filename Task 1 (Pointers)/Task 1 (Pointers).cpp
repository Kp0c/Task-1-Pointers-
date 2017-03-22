#include "stdafx.h"

#include "Task 1 (Pointers).h"

//TODO: DELETE ME!
#include <iostream>
using namespace std;

void printList(char** list) {
	for (int i = 0; i < StringListSize(list); i++)
	{
		std::cout << i+1 << ": " << list[i] << endl;
	}
}

void printCapacity(char** list) {
	cout << "Capacity: " << (int)(list[StringListSize(list)][1]) << endl;
}

//ENDTODO

int main()
{
	char** myList;
	StringListInit(&myList);
	///////////////////////////////////////////////////
	for (int i = 0; i < 16; i++)
	{
		char* buffer = reinterpret_cast<char*>(malloc(10 * sizeof(char*)));
		sprintf(buffer, "Hello, %d", i);
		StringListAdd(myList, /**/buffer/**//* "Hello"*/);

		printList(myList);
		printCapacity(myList);
	}

	printList(myList);
	printCapacity(myList);
	////////////////////////////////////////////////
	StringListDestroy(&myList);
    return 0;
}

void StringListInit(char*** list)
{
	*list = reinterpret_cast<char**>(calloc(10, sizeof(char**)));
	/*for (size_t i = 0; i < 10; i++)
	{
		(*list)[i] = reinterpret_cast<char*>(calloc(50, sizeof(char*)));
	}*/
	(*list)[0] = reinterpret_cast<char*>(calloc(2, sizeof(char*)));
	(*list)[0][1] = 10;
}

void StringListDestroy(char *** list)
{
	for (int i = 0; i < StringListSize(*list); i++)
	{
		free((*list)[i]);
		(*list)[i] = nullptr;
	}
	free(*list);
	*list = nullptr;
}

void StringListAdd(char ** list, char * str)
{
	int size = StringListSize(list);
	if (size + 2 > list[size][1]) 
	{
		char newSize = size*1.5;
		char** newMem = reinterpret_cast<char**> (realloc(list, newSize*sizeof(char**)));
		if (newMem != nullptr)
		{
			list = newMem;

			for (char i = size+1; i < newSize; i++)
			{
				list[i] = reinterpret_cast<char*>(calloc(50, sizeof(char*)));
			}

			list[size][1] = newSize;
		} else 
		{ 
			//TODO: throw exception
		}
	}

	list[size + 1][1] = list[size][1];
	list[size] = str;
}

int StringListSize(char ** list)
{
	int index = 0;
	while (*list[index] != '\0')
	{
		index++;
	}
	return index;
}
