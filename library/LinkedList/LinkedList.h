#ifndef HOMEWORK2_LINKEDMAP_H
#define HOMEWORK2_LINKEDMAP_H

#include <stdbool.h>
#include <stddef.h>

#define ELEMENT_DOES_NOT_EXIST -1
#define NON_EXISTENT_ELEMENT NULL

typedef struct LinkedListElement LinkedListElement;

typedef struct LinkedList LinkedList;

LinkedList* createNewLinkedList();
LinkedListElement* createNewElement(int data);
LinkedListElement* deleteElementAndGetNext(LinkedList* list, LinkedListElement* elementForDeletion);
LinkedListElement* getNextElement(LinkedListElement* element);
LinkedListElement* getHead(LinkedList* list);

void appendElement(LinkedList* list, LinkedListElement* element);
void appendNewElement(LinkedList* list, int data);
void printLinkedList(LinkedList* list);
void deleteLinkedList(LinkedList* list);
void setValue(LinkedListElement* element, int data);

int getValue(LinkedListElement* element);

#endif // HOMEWORK2_LINKEDMAP_H
