#include "LinkedList.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct LinkedListElement {
    int value;
    LinkedListElement* nextElement;
};

struct LinkedList {
    LinkedListElement* head;
    LinkedListElement* tail;
};

LinkedList* createNewLinkedList()
{
    LinkedList* newLinkedList = malloc(sizeof(LinkedList));
    newLinkedList->head = NULL;
    newLinkedList->tail = NULL;
    return newLinkedList;
}

LinkedListElement* createNewElement(int data)
{
    LinkedListElement* newElement = malloc(sizeof(LinkedListElement));

    newElement->value = data;
    newElement->nextElement = NULL;
    return newElement;
}

LinkedListElement* getHead(LinkedList* list)
{
    return list->head;
}

LinkedListElement* getNextElement(LinkedListElement* element)
{
    return element->nextElement;
}

int getValue(LinkedListElement* element)
{
    return element->value;
}

void setValue(LinkedListElement* element, int data)
{
    element->value = data;
}

void appendElement(LinkedList* list, LinkedListElement* element)
{
    if (!list->head)
        list->head = element;
    else
        list->tail->nextElement = element;
    list->tail = element;
}

void appendNewElement(LinkedList* list, int data)
{
    LinkedListElement* newElement = createNewElement(data);
    appendElement(list, newElement);
}

void printLinkedList(LinkedList* list)
{
    if (!list->head)
        printf("The linked list is empty!\n");
    for (LinkedListElement* currentElement = list->head; currentElement; currentElement = currentElement->nextElement)
        printf("%d\t", currentElement->value);
}

LinkedListElement* deleteElementAndGetNext(LinkedList* list, LinkedListElement* elementForDeletion)
{
    LinkedListElement* nextElement = elementForDeletion->nextElement;
    LinkedListElement* previousElement = NULL;

    for (LinkedListElement* currentElement = list->head; currentElement != elementForDeletion; elementForDeletion = elementForDeletion->nextElement) {
        previousElement = currentElement;
    }

    if (previousElement) {
        previousElement->nextElement = nextElement;
        if (!nextElement)
            list->tail = previousElement;
    } else if (nextElement)
        list->head = nextElement;

    free(elementForDeletion);

    return nextElement;
}

void deleteLinkedList(LinkedList* list)
{
    for (LinkedListElement* listElement = list->head; listElement; listElement = deleteElementAndGetNext(list, listElement)) { }
    free(list);
}