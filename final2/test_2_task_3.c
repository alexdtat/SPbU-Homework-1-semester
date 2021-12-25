#include "../library/DoublyLinkedListInt/DoublyLinkedListInt.h"
#include "errno.h"
#include <stdbool.h>
#include <stdio.h>

#define INPUT_FORMAT_VIOLATION -2
#define ERROR -1

bool isSymmetrical(DoublyLinkedList* list)
{
    DoublyLinkedListElement* currentLeft = getHead(list);
    DoublyLinkedListElement* currentRight = getTail(list);
    bool listIsSymmetrical = true;

    while (listIsSymmetrical && currentLeft != currentRight) {
        listIsSymmetrical = (getNumber(currentLeft) == getNumber(currentRight));
        currentLeft = getNextElement(currentLeft);
        if (currentLeft == currentRight)
            return listIsSymmetrical;

        currentRight = getPreviousElement(currentRight);
    }

    return listIsSymmetrical;
}

bool sequenceIsSymmetrical(char* sourcesFilePath, int* errorCode)
{
    errno = 0;
    FILE* sources = fopen(sourcesFilePath, "r");
    int currentNumber = 0;
    bool listIsSymmetrical = 0;

    if (!sources) {
        *errorCode = errno;
        return false;
    }

    DoublyLinkedList* list = createNewDoublyLinkedList();
    while (fscanf(sources, "%d", &currentNumber) != EOF)
        appendElement(list, createNewElement(currentNumber));

    listIsSymmetrical = isSymmetrical(list);

    fclose(sources);
    deleteDoublyLinkedList(list);
    *errorCode = 0;

    return listIsSymmetrical;
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("CONSOLE INPUT FORMAT VIOLATION!");
        return INPUT_FORMAT_VIOLATION;
    }

    int errorCode = 0;
    bool listIsSymmetrical = sequenceIsSymmetrical(argv[1], &errorCode);

    if (errorCode) {
        printf("Error! errno is:\t%d", errorCode);
        return ERROR;
    }

    if (listIsSymmetrical)
        printf("The sequence is symmetrical.\n");
    else
        printf("The sequence is NOT symmetrical.\n");

    return 0;
}
