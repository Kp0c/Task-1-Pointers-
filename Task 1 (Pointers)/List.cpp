#include "stdafx.h"

#include "List.h"

const int INITIAL_CAPACITY = 10;

void StringListInit(char*** list)
{
	if (*list == nullptr)
	{
		//allocate memory for the first INITIAL_CAPACITY strings
		*list = (char**)calloc(INITIAL_CAPACITY, sizeof(char**));
		//allocate memory for capacity and size info
		**list = (char*)calloc(2, sizeof(int));
		((int*)**list)[0] = INITIAL_CAPACITY;
	}
	else
	{
		throw "list already initiated";
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
	//size + 2 because first element, where we keep special info we don't calculate
	if (size + 2 > StringListCapacity(*list))
	{
		//actually it need to be 1.618 (see the golden ratio), but we don't need that accuracy
		int new_capacity = (int)(size * 1.5) + 1;
		char** new_memory = (char**)realloc(*list, new_capacity * sizeof(char**));
		//if memory allocated right
		if (new_memory != nullptr)
		{
			*list = new_memory;
			//fill all new elements by nullptr
			for (int i = size + 2; i < new_capacity; i++)
			{
				(*list)[i] = nullptr;
			}
			//set new capacity
			((int*)**list)[0] = new_capacity;
		}
		else
		{
			throw "allocation error";
		}
	}
	size = ++(((int*)**list)[1]);
	(*list)[size] = (char*)malloc(strlen(str) + 1);
	strcpy((*list)[size], str);
}

void Swap(char** a, char** b) 
{
	char* temporary_pointer = *a;
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
		int new_capacity = size * 1.5 + 1;

		char** new_memory = (char**)realloc(list, new_capacity * sizeof(char**));

		//if memory allocated - assign it to list, else do nothing, because it's not important
		if (new_memory != nullptr)
		{
			list = new_memory;
			((int*)list[0])[0] = new_capacity;
		}
	}
}

void StringListRemoveElementAt(char** list, int list_index_to_remove) {
	int size = StringListSize(list);

	//move elements for fill a gap
	//size + 1 because real size bigger because info at list[0]
	for (int i = list_index_to_remove; i < size + 1; i++)
	{
			Swap(&list[i], &list[i + 1]);
	}
	//new size
	((int*)list[0])[1] = size - 1;
	free(list[size]);
	list[size] = nullptr;
}

void StringListRemove(char** list, char* str)
{	
	//-1 to convert real_index to list_index
	int index_to_remove = StringListIndexOf(list, str) + 1;

	while (index_to_remove > -1)
	{
		StringListRemoveElementAt(list, index_to_remove);
		index_to_remove = StringListIndexOf(list, str);
	}

	TryToTrimMemory(list);
}

inline int StringListSize(char** list)
{
	return ((int*)*list)[1];
}

inline int StringListCapacity(char** list)
{
	return ((int*)*list)[0];
}

int StringListIndexOf(char** list, char* str)
{
	for (int i = 1; list[i] != nullptr && list[i][0] != '\0'; i++)
	{
		if (strcmp(list[i], str) == 0) 
		{
			// - 1 to convert list_index to real_index
			return i - 1;
		}
	}
	return -1;
}

void StringListRemoveDuplicates(char** list)
{
	int size = StringListSize(list);

	//compare all elements
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			//we add +1 because at list[0] list info, list indexes is (real_index+1)
			if (strcmp(list[i + 1], list[j + 1]) == 0)
			{
				StringListRemoveElementAt(list, j + 1);
				//list resized, so new size is..
				size = StringListSize(list);
				//we delete 1 element, so we need to decrement j for don't miss any element
				j--;
			}
		}
	}
	TryToTrimMemory(list);
}

void StringListReplaceInStrings(char** list, char* before, char* after)
{
	// +1 to convert list_index to real_index
	int index = StringListIndexOf(list, before) + 1;
	while (index != -1) {
		list[index] = (char*)realloc(list[index], strlen(after) + 1);
		strcpy(list[index], after);
		index = StringListIndexOf(list, before);
	}
}

int Comparator(const void* first, const void* second) {
	const char** a = (const char**)first;
	const char** b = (const char**)second;

	return strcmp(*a, *b);
}

void StringListSort(char** list)
{
	qsort(list + 1, StringListSize(list), sizeof(char*), Comparator);
}
