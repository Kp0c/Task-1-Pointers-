#include "stdafx.h"

#include "List.h"

const unsigned INITIAL_CAPACITY = 10;

void StringListInit(char*** list, bool force)
{
		if (force || *list == nullptr)
		{
			void* temporary_pointer = malloc(INITIAL_CAPACITY * sizeof(char*) + 2 * sizeof(unsigned));
			memset(temporary_pointer, 0, INITIAL_CAPACITY * sizeof(char*) + 2 * sizeof(unsigned));

			unsigned* capacity = (unsigned*)temporary_pointer;
			*capacity = INITIAL_CAPACITY;
			//capacity + 1 => size
			*list = (char**)(capacity + 2);
		}
		else
		{
			throw "list already initiated";
		}
}

void StringListDestroy(char*** list)
{
	if (list != nullptr && StringListIsValid(*list))
	{
		int size = StringListSize(*list);
		for (int i = 0; i < size; i++)
		{
			free((*list)[i]);
			(*list)[i] = nullptr;
		}
		//delete capacity and size too
		void* memory_for_free = ((unsigned*)*list) - 2;
		free(memory_for_free);
		*list = nullptr;
	}
}

void StringListAdd(char*** list, char* str)
{
	if (list != nullptr && StringListIsValid(*list))
	{
		unsigned size = StringListSize(*list);
		if (size + 1 > StringListCapacity(*list))
		{
			//actually it need to be 1.618 (see the golden ratio), but we don't need that accuracy
			unsigned new_capacity = (int)(size * 1.5);
			void* new_memory = (unsigned*)&((*list)[-2]);
			new_memory = (void*)realloc(new_memory, new_capacity * sizeof(char**) + 2 * sizeof(unsigned));
			//if memory allocated right
			if (new_memory != nullptr)
			{
				*list = (char**)(((unsigned*)(new_memory)) + 2);
				//fill all new elements by nullptr
				for (int i = size + 1; (unsigned)i < new_capacity; i++)
				{
					(*list)[i] = nullptr;
				}
				//set new capacity
				SetCapacity(*list, new_capacity);
			}
			else
			{
				throw "allocation error";
			}
		}
		//increment size
		size = (unsigned)((*list)[-1])++;
		//add string
		(*list)[size] = (char*)malloc(strlen(str) + 1);
		strcpy((*list)[size], str);
	}
}

void Swap(char** a, char** b) 
{
	char* temporary_pointer = *a;
	*a = *b;
	*b = temporary_pointer;
}

void TryToTrimMemory(char** list) 
{
	if (StringListIsValid(list))
	{
		unsigned size = StringListSize(list);
		unsigned capacity = StringListCapacity(list);

		//trim memory to 1.5 of real size if capacity 2 time more than real size
		if (capacity / (size + 1) > 2)
		{
			unsigned new_capacity = (int)(size * 1.5);
			if (new_capacity < INITIAL_CAPACITY)
			{
				new_capacity = INITIAL_CAPACITY;
			}

			void* new_memory = (unsigned*)&(list[-2]);
			new_memory = (void*)realloc(new_memory, new_capacity * sizeof(char*) + 2 * sizeof(unsigned));

			//if memory allocated - assign it to list, else do nothing, because it's not important
			if (new_memory != nullptr)
			{
				list = (char**)(((unsigned*)(new_memory)) + 2);
				SetCapacity(list, new_capacity);
			}
		}
	}
}

void StringListRemoveElementAt(char** list, unsigned list_index_to_remove) {
	unsigned size = StringListSize(list);

	//check for valid range
	if (StringListIsValid(list) && list_index_to_remove >= 0 && list_index_to_remove < size)
	{

		//move elements for fill a gap
		for (unsigned i = list_index_to_remove; i < size; i++)
		{
			Swap(&list[i], &list[i + 1]);
		}
		//new size
		--list[-1];
		//remove last position (it's already moved to a positon - 1)
		free(list[size]);
		list[size] = nullptr;
	}
}

void StringListRemove(char** list, char* str)
{	
	if (StringListIsValid(list))
	{
		int index_to_remove = StringListIndexOf(list, str);

		while (index_to_remove > -1)
		{
			StringListRemoveElementAt(list, index_to_remove);
			index_to_remove = StringListIndexOf(list, str);
		}

		TryToTrimMemory(list);
	}
}

unsigned StringListSize(char** list)
{
	if (StringListIsValid(list))
	{
		return (unsigned)list[-1];
	}
	else
	{
		return -1;
	}
}

unsigned StringListCapacity(char** list)
{
	if (StringListIsValid(list))
	{
		return (unsigned)list[-2];
	}
	else
	{
		return -1;
	}
}

void SetCapacity(char** list, unsigned value)
{
	unsigned* new_capacity_pointer = (unsigned*)&list[-2];
	*new_capacity_pointer = value;
}

int StringListIndexOf(char** list, char* str)
{
	unsigned size = StringListSize(list);
	if (StringListIsValid(list))
	{
		for (unsigned i = 0; i < size; i++)
		{
			if (strcmp(list[i], str) == 0)
			{
				return i;
			}
		}
	}
	return -1;
}

void StringListRemoveDuplicates(char** list)
{
	if (StringListIsValid(list))
	{
		int size = StringListSize(list);

		//compare all elements
		for (int i = 0; i < size - 1; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				if (strcmp(list[i], list[j]) == 0)
				{
					StringListRemoveElementAt(list, j);
					//list resized, so new size is..
					size = StringListSize(list);
					//we delete 1 element, so we need to decrement j for don't miss any element
					j--;
				}
			}
		}
		//after all deletes trim memory if it needed
		TryToTrimMemory(list);
	}
}

void StringListReplaceInStrings(char** list, char* before, char* after)
{
	if (StringListIsValid(list))
	{
		int index = StringListIndexOf(list, before);
		while (index != -1)
		{
			list[index] = (char*)realloc(list[index], strlen(after) + 1);
			strcpy(list[index], after);
			index = StringListIndexOf(list, before);
		}
	}
}

int Comparator(const void* first, const void* second) {
	char** a = (char**)first;
	char** b = (char**)second;

	return strcmp(*a, *b);
}

void StringListSort(char** list)
{
	if (StringListIsValid(list))
	{
		qsort(list, StringListSize(list), sizeof(char*), Comparator);
	}
}
