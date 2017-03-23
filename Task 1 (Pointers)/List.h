#pragma once

/* Initializes list */
void StringListInit(char*** list);
/* Destroy list and set pointer to nullptr. */
void StringListDestroy(char*** list);

/* Inserts value at the end of the list. */
void StringListAdd(char*** list, char* str);
/* Swap two strings. */
void Swap(char** a, char** b);
/* Trim memory when capacity bigger than real size 2 time more for avoid specific memory leak. */
void TryToTrimMemory(char** list);
/* Remove element at index_to_remove. */
void StringListRemoveElementAt(char** list, int index_to_remove);
/* Removes all occurrences of str in the list. */
void StringListRemove(char** list, char* str);

/* Returns the number of items in the list. */
inline int StringListSize(char** list);
/* Returns the capacity of the list. */
inline int StringListCapacity(char** list);
/* Returns the index position of the first occurrence of str in the list. */
int StringListIndexOf(char** list, char* str);

/* Removes duplicate entries from the list. */
void StringListRemoveDuplicates(char** list);
/* Replaces every occurrence of the before, in each of the string lists's strings, with after. */
void StringListReplaceInStrings(char** list, char* before, char* after);
/* Comparator for qsort */
int Comparator(const void* first, const void* second);
/* Sorts the list of strings in ascending order */
void StringListSort(char** list);