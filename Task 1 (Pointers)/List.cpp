#include "stdafx.h"

#include "List.h"

void StringListInit(char*** list)
{
	//allocate memory for the first 10 strings
	*list = reinterpret_cast<char**>(calloc(10, sizeof(char**)));
	//allocate memory for \0 and capaity info
	(*list)[0] = reinterpret_cast<char*>(calloc(2, sizeof(char*)));
	(*list)[0][1] = 10;
}

void StringListDestroy(char*** list)
{
	int size = StringListSize(*list);
	for (int i = 0; i < size; i++)
	{
		if ((*list)[i])
			free((*list)[i]);
		(*list)[i] = nullptr;
	}

	free(*list);
	*list = nullptr;
}

void StringListAdd(char** list, char* str)
{
	int size = StringListSize(list);
	//size + 2 because we always need empty string in rhe ned for determine end of list
	if (size + 2 > StringListCapacity(list))
	{
		//actually it need to be 1.618 (see the golden ratio), but we don't need that accuracy
		char newSize = (int)(size*1.5);
		char** newMem = reinterpret_cast<char**> (realloc(list, newSize * sizeof(char**)));
		//if memory allocated right
		if (newMem != nullptr)
		{
			list = newMem;
			//fill new memory by \0
			memset(list + size, '\0', (newSize - size) * sizeof(char*));
			//set new capacity
			list[0][strlen(list[0]) + 1] = newSize;
		}
		else
		{
			throw "allocation error";
		}
	}

	//if it's the first string, then push capacity after it
	if (size == 0) {
		char capacity = StringListCapacity(list);
		int stringLength = strlen(str);
		//allocate memory for string and capacity
		list[0] = reinterpret_cast<char*>(malloc(stringLength + 2));
		//insert string
		strcpy(list[0], str);
		//insert capacity
		list[0][stringLength + 1] = capacity;
	}
	else {
		list[size] = reinterpret_cast<char*>(malloc(strlen(str) + 1));
		strcpy(list[size], str);
	}
}

void StringListRemove(char** list, char* str)
{
	int indexToRemove = StringListIndexOf(list, str);
	//Nothing to delete
	if (indexToRemove == -1) return;

	int size = StringListSize(list);

	//move elements for fill a gap
	char* tmpPtr;
	for (int i = indexToRemove; i < size - 1; i++)
	{
		if (i == 0) 
		{
			int capacity = StringListCapacity(list);
			tmpPtr = list[0];
			list[0] = list[1];
			list[1] = tmpPtr;
			//resize strings and copy capacity
			list[0] = reinterpret_cast<char*>(realloc(list[0], strlen(list[0]) + 2));
			list[0][strlen(list[0]) + 1] = capacity;
		}
		else
		{
			tmpPtr = list[i];
			list[i] = list[i+1];
			list[i+1] = tmpPtr;
		}
	}

	free(list[size-1]);
	list[size-1] = nullptr;
	//TODO: trim memory if it needed
}

int StringListSize(char** list)
{
	int index = 0;
	while (list[index] != nullptr && list[index][0] != '\0')
	{
		index++;
	}
	return index;
}

inline char StringListCapacity(char** list)
{
	return list[0][strlen(list[0]) + 1];
}

int StringListIndexOf(char** list, char* str)
{
	for (int i = 0; list[i] != nullptr && list[i][0] != '\0'; i++)
	{
		if (strcmp(list[i], str) == 0) {
			return i;
		}
	}
	return -1;
}

void StringListRemoveDuplicates(char ** list)
{
	int size = StringListSize(list);

	//compare all elements
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i+1; j < size; j++)
		{
			if (strcmp(list[i], list[j]) == 0)
			{
				StringListRemove(list, list[j]);
				//list resized, so new size is..
				size = StringListSize(list);
				//we delete 1 element, so we need to decrement j for don't miss any element
				j--;
			}
		}
	}
}

void StringListReplaceInStrings(char ** list, char * before, char * after)
{
	int index = StringListIndexOf(list, before);
	while (index != -1) {
		//if it's the first index, then we need to save capacity
		if (index == 0)
		{
			int capacity = StringListCapacity(list);
			list[0] = reinterpret_cast<char*>(realloc(list[0], strlen(after) + 2));
			strcpy(list[index], after);
			list[0][strlen(list[0]) + 1] = capacity;
		}
		else
		{
			list[index] = reinterpret_cast<char*>(realloc(list[index], strlen(after) + 1));
			strcpy(list[index], after);
		}
		index = StringListIndexOf(list, before);
	}
}

int Comparator(const void* first, const void* second) {
	const char **a = reinterpret_cast<const char**>(const_cast<void*>(first));
	const char **b = reinterpret_cast<const char**>(const_cast<void*>(second));

	return strcmp(*a, *b);
}

void StringListSort(char** list)
{
	//save capacity
	int capacity = StringListCapacity(list);

	qsort(list, StringListSize(list), sizeof(char*), Comparator);

	//restore capacity value
	list[0] = reinterpret_cast<char*>(realloc(list[0], strlen(list[0]) + 2));
	list[0][strlen(list[0]) + 1] = capacity;
}
