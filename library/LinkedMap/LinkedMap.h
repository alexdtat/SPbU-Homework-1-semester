#ifndef HOMEWORK2_LINKEDMAP_H
#define HOMEWORK2_LINKEDMAP_H

#include <stdbool.h>

typedef struct LinkedMapElement {
    char* key;
    int value;
    struct LinkedMapElement* nextElement;
} LinkedMapElement;

typedef struct LinkedMap {
    int keySize;
    LinkedMapElement* head;
    LinkedMapElement* tail;
} LinkedMap;

LinkedMap* createNewLinkedMap();
LinkedMapElement* createNewElement(const char* data, int keySize);

void appendElement(LinkedMap* map, LinkedMapElement* element);
void resizeLinkedMapElementKey(LinkedMap* map, int newSize);
void put(LinkedMap* map, const char* userKey, int userValue);
void printLinkedMap(LinkedMap* map);
LinkedMapElement* deleteElementAndGetNext(LinkedMapElement* elementForDeletion);
void deleteLinkedMap(LinkedMap* map);

int get(LinkedMap* map, const char* userKey);

bool hasKey(LinkedMap* map, const char* userKey);

#endif // HOMEWORK2_LINKEDMAP_H
