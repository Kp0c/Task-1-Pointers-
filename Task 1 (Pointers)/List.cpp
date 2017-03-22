#include "stdafx.h"

#include "List.h"

const int INITIAL_CAPACITY = 10;

void StringListInit(char*** list)
{
	if (*list == nullptr)
	{
		//allocate memory for the first 10 strings
		*list = reinterpret_cast<char**>(calloc(10, sizeof(char**)));
		//allocate memory for \0 and capacity info
		(*list)[0] = reinterpret_cast<char*>(calloc(2, sizeof(char*)));
		(*list)[0][1] = INITIAL_CAPACITY;
	}
}

void StringListDestroy(char*** list)
{
	if (*list != nullptr)
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
}

void StringListAdd(char*** list, char* str)
{
	int size = StringListSize(*list);
	//size + 2 because we always need empty string in the end for determine end of list
	if (size + 2 > StringListCapacity(*list))
	{
		//actually it need to be 1.618 (see the golden ratio), but we don't need that accuracy
		char new_capacity = (int)(size*1.5);
		char** new_memory = reinterpret_cast<char**> (realloc(*list, new_capacity * sizeof(char**)));
		//if memory allocated right
		if (new_memory != nullptr)
		{
			*list = new_memory;
			//set all new elements by nullptr
			for (int i = size + 1; i < new_capacity; i++)
			{
				(*list)[i] = nullptr;
			}
			//set new capacity
			(*list[0])[strlen((*list)[0]) + 1] = new_capacity;
		}
		else
		{
			throw "allocation error";
		}
	}

	//if it's the first string, then push capacity after it
	if (size == 0) 
	{
		char capacity = StringListCapacity(*list);
		int string_length = strlen(str);
		//allocate memory for string and capacity
		(*list)[0] = reinterpret_cast<char*>(malloc(string_length + 2));
		//insert string
		strcpy((*list)[0], str);
		//insert capacity
		(*list)[0][string_length + 1] = capacity;
	}
	else 
	{
		(*list)[size] = reinterpret_cast<char*>(malloc(strlen(str) + 1));
		strcpy((*list)[size], str);
	}
}

void Swap(char** a, char** b) 
{
	char* temporary_pointer;
	temporary_pointer = *a;
	*a = *b;
	*b = temporary_pointer;
}

void TryToTrimMemory(char** list) 
{
	int size = StringListSize(list);
	int capacity = StringListCapacity(list);

	//trim memory to 1.5 of real size if capacity 2 time more than real size
	if (capacity / size > 2) 
	{
		int new_capacity = size * 1.5;

		char** new_memory = reinterpret_cast<char**> (realloc(list, new_capacity * sizeof(char**)));

		//if memory allocated - assign it to list, else do nothing, because it's not important
		if (new_memory != nullptr)
		{
			list = new_memory;
			list[0][strlen(list[0]) + 1] = new_capacity;
		}
	}
}

void StringListRemoveElementAt(char** list, int index_to_remove) {
	int size = StringListSize(list);

	//move elements for fill a gap
	for (int i = index_to_remove; i < size - 1; i++)
	{
		//if it's the first string - we need to save capacity
		if (i == 0)
		{
			int capacity = StringListCapacity(list);
			Swap(&list[0], &list[1]);
			//resize strings and copy capacity
			list[0] = reinterpret_cast<char*>(realloc(list[0], strlen(list[0]) + 2));
			list[0][strlen(list[0]) + 1] = capacity;
		}
		else
		{
			Swap(&list[i], &list[i + 1]);
		}
	}

	free(list[size - 1]);
	list[size - 1] = nullptr;
}

void StringListRemove(char** list, char* str)
{	
	int index_to_remove = StringListIndexOf(list, str);

	while (index_to_remove != -1)
	{
		StringListRemoveElementAt(list, index_to_remove);
		index_to_remove = StringListIndexOf(list, str);
	}

	TryToTrimMemory(list);
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
		if (strcmp(list[i], str) == 0) 
		{
			return i;
		}
	}
	return -1;
}

void StringListRemoveDuplicates(char** list)
{
	int size = StringListSize(list);

	//compare all elements
	for (int i = 0; i < size - 1; i++)
		for (int j = i+1; j < size; j++)
			if (strcmp(list[i], list[j]) == 0)
			{
				StringListRemoveElementAt(list, j);
				//list resized, so new size is..
				size = StringListSize(list);
				//we delete 1 element, so we need to decrement j for don't miss any element
				j--;
			}
	TryToTrimMemory(list);
}

void StringListReplaceInStrings(char** list, char* before, char* after)
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
	const char** a = reinterpret_cast<const char**>(const_cast<void*>(first));
	const char** b = reinterpret_cast<const char**>(const_cast<void*>(second));

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
