#include "LinkedMap.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct LinkedMapElement {
    char* key;
    int value;
    LinkedMapElement* nextElement;
};

struct LinkedMap {
    LinkedMapElement* head;
    LinkedMapElement* tail;
};

LinkedMap* createNewLinkedMap()
{
    LinkedMap* newLinkedMap = malloc(sizeof(LinkedMap));
    newLinkedMap->head = NULL;
    newLinkedMap->tail = NULL;
    return newLinkedMap;
}

LinkedMapElement* createNewElement(const char* data)
{
    LinkedMapElement* newElement = malloc(sizeof(LinkedMapElement));
    newElement->key = calloc(strlen(data) + 1, sizeof(char));

    strcpy(newElement->key, data);
    newElement->nextElement = NULL;
    newElement->value = 0;
    return newElement;
}

LinkedMapElement* getHead(LinkedMap* map)
{
    return map->head;
}

LinkedMapElement* getNextElement(LinkedMapElement* element)
{
    return element->nextElement;
}

char* getKey(LinkedMapElement* element)
{
    return element->key;
}

int getValue(LinkedMapElement* element)
{
    return element->value;
}

LinkedMapElement* findElementByKey(LinkedMap* map, const char* userKey)
{
    for (LinkedMapElement* mapElement = map->head; mapElement != NULL; mapElement = mapElement->nextElement) {
        if (strcmp(mapElement->key, userKey) == 0)
            return mapElement;
    }

    return NON_EXISTENT_ELEMENT;
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
    if (!hasKey(map, userKey)) {
        appendElement(map, createNewElement(userKey));
        map->tail->value = 1;
    } else
        findElementByKey(map, userKey)->value = userValue;
}

int get(LinkedMap* map, const char* userKey)
{
    LinkedMapElement* element = findElementByKey(map, userKey);

    if (element)
        return element->value;

    return ELEMENT_DOES_NOT_EXIST;
}

bool hasKey(LinkedMap* map, const char* userKey)
{
    return (findElementByKey(map, userKey) != NON_EXISTENT_ELEMENT);
}

void printLinkedMap(LinkedMap* map)
{
    if (!map->head)
        printf("The linked map is empty!\n");
    for (LinkedMapElement* currentElement = map->head; currentElement; currentElement = currentElement->nextElement)
        printf("%s\t%d\n", currentElement->key, currentElement->value);
}

LinkedMapElement* deleteElementAndGetNext(LinkedMapElement* elementForDeletion)
{
    LinkedMapElement* nextElement = elementForDeletion->nextElement;

    free(elementForDeletion->key);
    free(elementForDeletion);

    return nextElement;
}

void deleteLinkedMap(LinkedMap* map)
{
    for (LinkedMapElement* mapElement = map->head; mapElement; mapElement = deleteElementAndGetNext(mapElement)) {
    }
    free(map);
}