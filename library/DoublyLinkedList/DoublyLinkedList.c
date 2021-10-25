#include "DoublyLinkedList.h"
#include <stdio.h>
#include <stdlib.h>

struct DoublyLinkedListElement {
    char symbol;
    DoublyLinkedListElement* nextElement;
    DoublyLinkedListElement* previousElement;
};

struct DoublyLinkedList {
    DoublyLinkedListElement* head;
    DoublyLinkedListElement* tail;
};

DoublyLinkedList* createNewDoublyLinkedList()
{
    DoublyLinkedList* newDoublyLinkedList = malloc(sizeof(DoublyLinkedList));
    newDoublyLinkedList->head = NULL;
    newDoublyLinkedList->tail = NULL;
    return newDoublyLinkedList;
}

DoublyLinkedListElement* createNewElement(char data)
{
    DoublyLinkedListElement* newElement = malloc(sizeof(struct DoublyLinkedListElement));
    newElement->symbol = data;

    newElement->nextElement = NULL;
    newElement->previousElement = NULL;
    return newElement;
}

DoublyLinkedListElement* getHead(DoublyLinkedList* list)
{
    return list->head;
}

DoublyLinkedListElement* getTail(DoublyLinkedList* list)
{
    return list->tail;
}

DoublyLinkedListElement* getNextElement(DoublyLinkedListElement* element)
{
    return element->nextElement;
}

DoublyLinkedListElement* getPreviousElement(DoublyLinkedListElement* element)
{
    return element->previousElement;
}

char getSymbol(DoublyLinkedListElement* element)
{
    return element->symbol;
}

DoublyLinkedListElement* findElementBySymbolSince(char userSymbol, DoublyLinkedListElement* start)
{
    for (DoublyLinkedListElement* listElement = start; listElement; listElement = listElement->nextElement) {
        if (listElement->symbol == userSymbol)
            return listElement;
    }

    return NON_EXISTENT_ELEMENT;
}

void appendElement(DoublyLinkedList* list, struct DoublyLinkedListElement* element)
{
    if (!list->head)
        list->head = element;
    else {
        list->tail->nextElement = element;
        element->previousElement = list->tail;
    }
    list->tail = element;
}

void insertElementAfter(DoublyLinkedList* list, DoublyLinkedListElement* insertedElement, DoublyLinkedListElement* elementBefore)
{
    if (!list->head && !list->tail) {
        list->head = insertedElement;
        list->tail = insertedElement;
        return;
    }

    insertedElement->previousElement = elementBefore;
    if (elementBefore) {
        if (elementBefore->nextElement) {
            elementBefore->nextElement->previousElement = insertedElement;
            insertedElement->nextElement = elementBefore->nextElement;
            elementBefore->nextElement = insertedElement;
        } else {
            insertedElement->previousElement = list->tail;
            list->tail->nextElement = insertedElement;
            list->tail = insertedElement;
        }
    } else {
        insertedElement->nextElement = list->head;
        list->head = insertedElement;
    }
}

void printDoublyLinkedList(DoublyLinkedList* list)
{
    if (!list->head)
        printf("The linked map is empty!\n");
    for (DoublyLinkedListElement* currentElement = list->head; currentElement; currentElement = currentElement->nextElement)
        printf("%c", currentElement->symbol);
}

DoublyLinkedListElement* deleteElementAndGetNext(DoublyLinkedList* list, DoublyLinkedListElement* elementForDeletion)
{
    if (elementForDeletion->previousElement)
        elementForDeletion->previousElement->nextElement = elementForDeletion->nextElement;
    else
        list->head = elementForDeletion->nextElement;
    if (elementForDeletion->nextElement)
        elementForDeletion->nextElement->previousElement = elementForDeletion->previousElement;
    else
        list->tail = elementForDeletion->previousElement;

    DoublyLinkedListElement* nextElement = elementForDeletion->nextElement;

    free(elementForDeletion);

    return nextElement;
}

void deleteDoublyLinkedList(DoublyLinkedList* list)
{
    for (struct DoublyLinkedListElement* listElement = list->head; listElement; listElement = deleteElementAndGetNext(list, listElement)) { }
    free(list);
}