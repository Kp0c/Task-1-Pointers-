#pragma once

/* Initializes list 
 * if force == true - list will èó initializeâ anyway. ATTENTION: may cause memory leak
 */
void StringListInit(char*** list, bool force = false);
/* Destroy list and set pointer to nullptr. */
void StringListDestroy(char*** list);

/* Inserts value at the end of the list. */
void StringListAdd(char*** list, const char* str);
/* Swap two strings. */
void Swap(const char** a, const char** b);
/* Trim memory when capacity bigger than real size 2 time more for avoid specific memory leak. */
void TryToTrimMemory(char** list);
/* Remove element at index_to_remove. */
void StringListRemoveElementAt(char** list, unsigned index_to_remove);
/* Removes all occurrences of str in the list. */
void StringListRemove(char** list, const char* str);

/* Returns the number of items in the list. */
unsigned StringListSize(const char* const* list);
/* Returns the capacity of the list. */
unsigned StringListCapacity(const char* const* list);
/* Set capacity to value */
void SetCapacity(char* const* list, unsigned value);
/* Check if list valid */
inline bool StringListIsValid(const char* const* list)
{
	if (list != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}
inline bool StringListIsValid(const char* const* const* list)
{
	if (list != nullptr)
	{
		return StringListIsValid(*list);
	}
	else
	{
		return false;
	}
}

/* Returns the index position of the first occurrence of str in the list. */
int StringListIndexOf(const char* const* list, const char* str);

/* Removes duplicate entries from the list. */
void StringListRemoveDuplicates(char** list);
/* Replaces every occurrence of the before, in each of the string lists's strings, with after. */
void StringListReplaceInStrings(char** list, const char* before, const char* after);
/* Comparator for qsort */
int Comparator(const void* first, const void* second);
/* Sorts the list of strings in ascending order */
void StringListSort(char** list);