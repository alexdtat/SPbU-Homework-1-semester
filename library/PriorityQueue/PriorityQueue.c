#include "PriorityQueue.h"
#include "../DoublyLinkedListInt/DoublyLinkedListInt.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Element {
    int priority;
    DoublyLinkedList* values;
} Element;

typedef struct BinomialHeap {
    Element** array;
    int size;
    int allocatedSize;
} BinomialHeap;

Element* createElement(int priority)
{
    Element* newElement = malloc(sizeof(Element));
    newElement->priority = priority;
    newElement->values = createNewDoublyLinkedList();

    return newElement;
}

void deleteElement(Element* element)
{
    deleteDoublyLinkedList(element->values);
    free(element);
}

void resizeArray(BinomialHeap* heap)
{
    heap->allocatedSize *= 2;
    heap->array = realloc(heap->array, heap->allocatedSize * sizeof(Element));
}

void swap(Element* a, Element* b)
{
    Element temporary = *b;
    *b = *a;
    *a = temporary;
}

void heapify(BinomialHeap* heap, int position)
{
    int size = heap->size;
    Element** array = heap->array;

    if (size == 1) {
        printf("Single element in the heap");
    } else {
        int largest = position;
        int left = 2 * position + 1;
        int right = 2 * position + 2;
        if (left < size && array[left]->priority > array[largest]->priority)
            largest = left;
        if (right < size && array[right]->priority > array[largest]->priority)
            largest = right;

        if (largest != position) {
            swap(array[position], array[largest]);
            heapify(heap, largest);
        }
    }
}

void insert(BinomialHeap* heap, int newPriority)
{
    int* size = &heap->size;
    Element** array = heap->array;
    if (*size == 0) {
        array[0] = createElement(newPriority);
        *size += 1;
    } else {
        array[*size] = createElement(newPriority);
        *size += 1;
        for (int i = *size / 2 - 1; i >= 0; i--) {
            heapify(heap, i);
        }
    }

    if (heap->size == heap->allocatedSize)
        resizeArray(heap);
}

void deleteRoot(BinomialHeap* heap, int priority)
{
    int position = 0;
    int* size = &heap->size;
    Element** array = heap->array;

    for (; position < *size; position++) {
        if (priority == array[position]->priority)
            break;
    }

    deleteElement(array[priority]);

    swap(array[priority], array[*size - 1]);
    size -= 1;
    for (int j = *size / 2 - 1; j >= 0; j--)
        heapify(heap, j);
}

void printArray(int array[], int size)
{
    for (int i = 0; i < size; ++i)
        printf("%d ", array[i]);
    printf("\n");
}

void put(BinomialHeap* heap, int number, int priority)
{
    for (int i = 0; i < heap->size; i++) {
        if (deleteElementByNumber(heap->array[i]->values, number)) {
            if (isEmpty(heap->array[i]->values))
                deleteRoot(heap, heap->array[i]->priority);
            break;
        }

        if (heap->array[i]->priority == priority)
            appendElement(heap->array[i]->values, createNewElement(number));
    }
}
