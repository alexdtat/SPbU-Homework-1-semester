#ifndef HOMEWORK2_DOUBLYLINKEDLIST_H
#define HOMEWORK2_DOUBLYLINKEDLIST_H

#include <stdbool.h>
#include <stddef.h>

#define ELEMENT_DOES_NOT_EXIST -1
#define NON_EXISTENT_ELEMENT 0

typedef struct DoublyLinkedListElement DoublyLinkedListElement;

typedef struct DoublyLinkedList DoublyLinkedList;

DoublyLinkedList* createNewDoublyLinkedList();
DoublyLinkedListElement* createNewElement(int data);
DoublyLinkedListElement* deleteElementAndGetNext(DoublyLinkedList* list, DoublyLinkedListElement* elementForDeletion);
DoublyLinkedListElement* getNextElement(DoublyLinkedListElement* element);
DoublyLinkedListElement* getPreviousElement(DoublyLinkedListElement* element);
DoublyLinkedListElement* getHead(DoublyLinkedList* list);
DoublyLinkedListElement* getTail(DoublyLinkedList* list);
DoublyLinkedListElement* findElementByNumberSince(int userNumber, DoublyLinkedListElement* start);

void appendElement(DoublyLinkedList* list, DoublyLinkedListElement* element);
void printDoublyLinkedList(DoublyLinkedList* list);
void insertElementAfter(DoublyLinkedList* list, DoublyLinkedListElement* insertedElement, DoublyLinkedListElement* elementBefore);
void deleteDoublyLinkedList(DoublyLinkedList* list);

int getNumber(DoublyLinkedListElement* element);
DoublyLinkedListElement* findElementByNumber(DoublyLinkedList* list, int userNumber);
bool deleteElementByNumber(DoublyLinkedList* list, int userNumber);
bool isEmpty(DoublyLinkedList* list);

#endif // HOMEWORK2_DOUBLYLINKEDLIST_H
