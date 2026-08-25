#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct
{
	char* key;
	size _len;
	void* value; // can be NULL - but not CAIRO
} MapEntry;

typedef struct
{
	size_t count;
	size_t capacity;
	MapEntry* entries;
} Map;

void mapInit(Map* map);
void mapFree(Map* map);
void* mapGet(Map* map, const char* key, size keyLen);
void mapPut(Map* map, const char* key, size keyLen, void* value);
bool mapHas(Map* map, const char* key, size keylen);
void mapPrint(Map* map, void (*printFun)(void* value));
void mapRemove(Map* map, const char* key, size keyLen);

#endif
#if __INCLUDE_LEVEL__ == 0

#include "log.c"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAX_LOAD 0.5
#define INITIAL_CAPACITY 16
#define GROW_FACTOR 2
// A sentinel value which can NOT be inserted into the array.
#define CAIRO ((void*)-1)

void mapInit(Map* map)
{
	map->count = 0;
	map->capacity = INITIAL_CAPACITY;
	map->entries = calloc((size_t)map->capacity, sizeof(MapEntry));
	if (map->entries == NULL)
	{
		logFatal("Could not allocate enough memory for Hash Map.");
	}
}

void mapFree(Map* map)
{
	if (map->entries != NULL)
	{
		free(map->entries);
	}
	map->count = 0;
	map->capacity = 0;
	map->entries = NULL;
}

// Adapted from Jenkin's hash function 'One at a time'
// see https://www.burtleburtle.net/bob/hash/doobs.html
size_t hashKey(const char* key, size keyLen)
{
	size_t hash = 0;
	for (size i = 0; i < keyLen; i++)
	{
		hash += (size_t)key[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;
}

MapEntry* findEntry(MapEntry* entries, size capacity, const char* key, size keyLen)
{
	size_t index = hashKey(key, keyLen) & (capacity - 1);
	MapEntry* tombstone = NULL;

	MapEntry* entry;
	while (true)
	{
		entry = &entries[index];

		if (entry->key == NULL)
		{
			if (entry->value == CAIRO)
			{

				if (tombstone == NULL)
				{
					tombstone = entry;
				}
			}
			else if (entry->value == NULL)
			{
				if (tombstone != NULL)
				{
					return tombstone;
				}
				else
				{
					return entry;
				}
			}
			else
			{
				logFatal("Unreachable case: Hashmap contains value without key.");
			}
		}
		else if (entry->key == key || (entry->_len == keyLen && memcmp(entry->key, key, (size_t)keyLen) == 0))
		{
			return entry;
		}
		index = (index + 1) & (capacity - 1);
	}
}

static void increaseCapacity(Map* map, size capacity)
{
	MapEntry* entries = calloc(capacity, sizeof(MapEntry));
	if (entries == NULL)
	{
		logFatal("Could not allocate enough memory for Hash Map.");
	}
	map->count = 0;
	for (size_t i = 0; i < map->capacity; i++)
	{
		MapEntry* entry = &map->entries[i];
		if (entry->key == NULL)
			continue;
		map->count++;

		MapEntry* dest = findEntry(entries, capacity, entry->key, entry->_len);
		dest->key = entry->key;
		dest->_len = entry->_len;
		dest->value = entry->value;
	}

	free(map->entries);
	map->entries = entries;
	map->capacity = capacity;
}

void* mapGet(Map* map, const char* key, size keyLen)
{
	if (map->count == 0 || key == NULL)
		return NULL;

	MapEntry* entry = findEntry(map->entries, map->capacity, key, keyLen);

	if (entry->key == NULL)
		return NULL;

	return entry->value;
}

bool mapHas(Map* map, const char* key, size keyLen) { return mapGet(map, key, keyLen) != NULL; }

void mapPut(Map* map, const char* key, size keyLen, void* value)
{
	if (key == NULL)
	{
		logFatal("Can not insert empty key into hash map.");
	}

	if ((map->count + 1) > map->capacity * MAX_LOAD)
	{
		increaseCapacity(map, map->capacity * GROW_FACTOR);
	}

	MapEntry* entry = findEntry(map->entries, map->capacity, key, keyLen);
	bool isNew = (entry->key == NULL);
	if (isNew)
	{
		map->count++;
	}

	entry->key = (char*)key;
	entry->_len = keyLen;
	entry->value = value;
}

void mapRemove(Map* map, const char* key, size keyLen)
{
	if (map->count == 0)
		return;
	MapEntry* entry = findEntry(map->entries, map->capacity, key, keyLen);
	if (entry->key == NULL)
		return;
	entry->key = NULL;
	entry->value = CAIRO;
	map->count--;
}

void mapPrint(Map* map, void (*printFun)(void* value))
{
	MapEntry* entryPtr;
	for (int i = 0; (size_t)i < map->capacity; i++)
	{
		entryPtr = &map->entries[i];

		if (!entryPtr)
			continue;
		if (entryPtr->key == NULL || entryPtr->value == CAIRO)
			continue;

		printf("%.*s: ", (int)entryPtr->_len, entryPtr->key);
		(*printFun)(entryPtr->value);
		printf("\n");
	}
}

#endif
