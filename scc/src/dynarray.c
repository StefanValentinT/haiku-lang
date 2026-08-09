#ifndef DYNARRAY_H
#define DYNARRAY_H

#include <stddef.h>

typedef struct
{
	size_t count;
	size_t capacity;
	size_t elemSize;
	void* items;
} DynArray;

DynArray initArray(int capac, size_t elemSize);
void freeArray(DynArray* arr);
void appendArray(DynArray* arr, void* value);
void* getArray(DynArray* arr, int index);

#endif
#if __INCLUDE_LEVEL__ == 0

#include "log.c"
#include <stdlib.h>
#include <string.h>

#define GROWTH_FACTOR 2

DynArray initArray(int capacity, size_t elemSize)
{
	return (DynArray){.count = 0,
	                  .capacity = (size_t)capacity,
	                  .elemSize = elemSize,
	                  .items = (void*)malloc((size_t)capacity * elemSize)};
}

void appendArray(DynArray* arr, void* value)
{
	if ((arr->count) >= arr->capacity)
	{
		arr->capacity *= GROWTH_FACTOR;
		void* temp = realloc(arr->items, (size_t)arr->capacity * arr->elemSize);
		if (temp == NULL)
		{
			logFatal("Could not allocate enough memory for dynamic array");
		}
		arr->items = temp;
	}
	char* pos = (char*)arr->items + (arr->count * arr->elemSize);
	memcpy(pos, value, arr->elemSize);
	arr->count++;
}

void* getArray(DynArray* arr, int index) { return (char*)arr->items + ((size_t)index * arr->elemSize); }

void freeArray(DynArray* arr)
{
	arr->count = 0;
	arr->capacity = 0;
	arr->elemSize = 0;
	free(arr->items);
}

#endif
