#include "LinkedMap.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

bool stringsAreSimilar(const char* string1, const char* string2, int stringsSize)
{
    for (int i = 0; i < stringsSize; i++) {
        if (string1[i] != string2[i])
            return false;
    }
    return true;
}

LinkedMap* createNewLinkedMap()
{
    LinkedMap* newLinkedMap = malloc(sizeof(LinkedMap));
    newLinkedMap->head = NULL;
    newLinkedMap->tail = NULL;
    newLinkedMap->keySize = 0;
    return newLinkedMap;
}

void resizeLinkedMapElementKey(LinkedMap* map, int newSize)
{
    map->keySize = newSize;
}

LinkedMapElement* createNewElement(const char* data, int keySize)
{
    LinkedMapElement* newElement = malloc(sizeof(LinkedMapElement));
    newElement->key = calloc(keySize, sizeof(char));
    for (int i = 0; i < keySize; i++)
        newElement->key[i] = data[i];
    newElement->nextElement = NULL;
    newElement->value = 0;
    return newElement;
}

void appendElement(LinkedMap* map, LinkedMapElement* element)
{
    if (!map->head)
        map->head = element;
    else
        map->tail->nextElement = element;
    map->tail = element;
}

void put(LinkedMap* map, const char* userKey, int userValue)
{
    for (LinkedMapElement* mapElement = map->head; mapElement != NULL; mapElement = mapElement->nextElement) {
        if (stringsAreSimilar(mapElement->key, userKey, map->keySize))
            mapElement->value = userValue;
    }
}

int get(LinkedMap* map, const char* userKey)
{
    for (LinkedMapElement* mapElement = map->head; mapElement != NULL; mapElement = mapElement->nextElement) {
        if (stringsAreSimilar(mapElement->key, userKey, map->keySize))
            return mapElement->value;
    }
    return -1;
}

bool hasKey(LinkedMap* map, const char* userKey)
{
    for (LinkedMapElement* mapElement = map->head; mapElement != NULL; mapElement = mapElement->nextElement) {
        if (stringsAreSimilar(mapElement->key, userKey, map->keySize))
            return true;
    }

    return false;
}

void printLinkedMap(LinkedMap* map)
{
    LinkedMapElement* currentElement = map->head;
    if (!currentElement)
        printf("The linked map is empty!\n");
    while (currentElement) {
        printf("%s\t%d\n", currentElement->key, currentElement->value);
        currentElement = currentElement->nextElement;
    }
}

LinkedMapElement* deleteElementAndGetNext(LinkedMapElement* elementForDeletion)
{
    LinkedMapElement* nextElement = NULL;

    nextElement = elementForDeletion->nextElement;
    free((char*)elementForDeletion->key);
    elementForDeletion->nextElement = NULL;
    free(elementForDeletion);

    return nextElement;
}

void deleteLinkedMap(LinkedMap* map)
{
    LinkedMapElement* firstNotRemovedElement = NULL;
    for (LinkedMapElement* mapElement = map->head; mapElement != NULL; mapElement = firstNotRemovedElement)
        firstNotRemovedElement = deleteElementAndGetNext(mapElement);

    map->head = NULL;
    map->tail = NULL;
    free(map);
}