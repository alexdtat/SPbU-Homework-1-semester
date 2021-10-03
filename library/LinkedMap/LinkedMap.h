#ifndef HOMEWORK2_LINKEDMAP_H
#define HOMEWORK2_LINKEDMAP_H

#include <stdbool.h>
#include <stddef.h>

#define ELEMENT_DOES_NOT_EXIST -1
#define NON_EXISTENT_ELEMENT NULL

typedef struct LinkedMapElement LinkedMapElement;

typedef struct LinkedMap LinkedMap;

LinkedMap* createNewLinkedMap();
LinkedMapElement* createNewElement(const char* data);
LinkedMapElement* deleteElementAndGetNext(LinkedMap* map, LinkedMapElement* elementForDeletion);
LinkedMapElement* getNextElement(LinkedMapElement* element);
LinkedMapElement* getHead(LinkedMap* map);
LinkedMapElement* findElementByKey(LinkedMap* map, const char* userKey);

void appendElement(LinkedMap* map, LinkedMapElement* element);
void put(LinkedMap* map, const char* userKey, int userValue);
void printLinkedMap(LinkedMap* map);
void deleteLinkedMap(LinkedMap* map);

int get(LinkedMap* map, const char* userKey);
int getValue(LinkedMapElement* element);

char* getKey(LinkedMapElement* element);

bool hasKey(LinkedMap* map, const char* userKey);

#endif // HOMEWORK2_LINKEDMAP_H
