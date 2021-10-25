#ifndef HOMEWORK2_DOUBLYLINKEDLIST_H
#define HOMEWORK2_DOUBLYLINKEDLIST_H

#include <stdbool.h>
#include <stddef.h>

#define ELEMENT_DOES_NOT_EXIST -1
#define NON_EXISTENT_ELEMENT NULL

typedef struct DoublyLinkedListElement DoublyLinkedListElement;

typedef struct DoublyLinkedList DoublyLinkedList;

DoublyLinkedList* createNewDoublyLinkedList();
DoublyLinkedListElement* createNewElement(char data);
DoublyLinkedListElement* deleteElementAndGetNext(DoublyLinkedList* list, DoublyLinkedListElement* elementForDeletion);
DoublyLinkedListElement* getNextElement(DoublyLinkedListElement* element);
DoublyLinkedListElement* getPreviousElement(DoublyLinkedListElement* element);
DoublyLinkedListElement* getHead(DoublyLinkedList* list);
DoublyLinkedListElement* getTail(DoublyLinkedList* list);
DoublyLinkedListElement* findElementBySymbolSince(char userSymbol, DoublyLinkedListElement* start);

void appendElement(DoublyLinkedList* list, DoublyLinkedListElement* element);
void printDoublyLinkedList(DoublyLinkedList* list);
void insertElementAfter(DoublyLinkedList* list, DoublyLinkedListElement* insertedElement, DoublyLinkedListElement* elementBefore);
void deleteDoublyLinkedList(DoublyLinkedList* list);

char getSymbol(DoublyLinkedListElement* element);

#endif // HOMEWORK2_DOUBLYLINKEDLIST_H
