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

void StringListDestroy(char *** list)
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

void StringListAdd(char ** list, char * str)
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

int StringListSize(char ** list)
{
	int index = 0;
	while (list[index] != nullptr && list[index][0] != '\0')
	{
		index++;
	}
	return index;
}

inline char StringListCapacity(char ** list)
{
	return list[0][strlen(list[0]) + 1];
}
