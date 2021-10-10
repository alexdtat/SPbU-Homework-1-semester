#include "../library/DoublyLinkedList/DoublyLinkedList.h"
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define DELETION_ERROR -1
#define INSERTION_ERROR -2
#define REPLACEMENT_ERROR -3

bool find(DoublyLinkedListElement* start, const char* sequence, DoublyLinkedListElement** matchStart, DoublyLinkedListElement** matchEnd)
{
    DoublyLinkedListElement* elementOfSequence = NULL;
    int sequenceLength = strlen(sequence);

    if (!strlen(sequence))
        return start;

    for (DoublyLinkedListElement* currentElement = start; currentElement; currentElement = getNextElement(currentElement)) {
        elementOfSequence = currentElement;
        for (int i = 0; elementOfSequence && getSymbol(elementOfSequence) == sequence[i]; i++) {
            if (i == sequenceLength - 1) {
                *matchStart = currentElement;
                *matchEnd = elementOfSequence;
                return true;
            }
            elementOfSequence = getNextElement(elementOfSequence);
        }
    }

    return false;
}

void insertFragmentAfterElement(DoublyLinkedList* list, DoublyLinkedListElement* elementBefore, const char* fragment)
{
    DoublyLinkedListElement* currentPosition = elementBefore;
    int fragmentLength = strlen(fragment);

    for (int i = 0; i < fragmentLength; i++) {
        insertElementAfter(list, createNewElement(fragment[i]), currentPosition);
        currentPosition = getNextElement(currentPosition);
    }
}

void deleteFragmentInRange(DoublyLinkedList* list, DoublyLinkedListElement* start, DoublyLinkedListElement* end)
{
    for (DoublyLinkedListElement* current = start; current != end; current = deleteElementAndGetNext(list, current)) { }
}

bool insertFragment(DoublyLinkedList* list, const char* start, const char* fragment)
{
    DoublyLinkedListElement* startingPosition = NULL;
    DoublyLinkedListElement* endingPosition = NULL;
    if (!find(getHead(list), start, &startingPosition, &endingPosition))
        return false;

    insertFragmentAfterElement(list, endingPosition, fragment);

    return true;
}

bool deleteFragment(DoublyLinkedList* list, const char* start, const char* end)
{
    DoublyLinkedListElement* startingPosition = NULL;
    DoublyLinkedListElement* startSequenceLastElement = NULL;
    if (!find(getHead(list), start, &startingPosition, &startSequenceLastElement))
        return false;

    DoublyLinkedListElement* endSequenceFirstElement = NULL;
    DoublyLinkedListElement* lastElement = NULL;
    if (!find(getNextElement(startSequenceLastElement), end, &endSequenceFirstElement, &lastElement))
        return false;
    DoublyLinkedListElement* endingPosition = getNextElement(lastElement);

    deleteFragmentInRange(list, startingPosition, endingPosition);
    return true;
}

bool replaceFragment(DoublyLinkedList* list, const char* template, const char* fragment)
{
    DoublyLinkedListElement* startingPosition = NULL;
    DoublyLinkedListElement* lastElement = NULL;
    if (!find(getHead(list), template, &startingPosition, &lastElement))
        return false;

    DoublyLinkedListElement* elementBeforeStart = getPreviousElement(startingPosition);
    DoublyLinkedListElement* endingPosition = getNextElement(lastElement);

    deleteFragmentInRange(list, startingPosition, endingPosition);
    insertFragmentAfterElement(list, elementBeforeStart, fragment);

    return true;
}

int recoverDNA(const char* sourcesFilePath, const char* resultsFilePath)
{
    char currentCommand[8];
    char firstArgument[128];
    char secondArgument[128];
    int sequenceSize = 0;
    int numberOfLines = 0;
    errno = 0;

    FILE* sourcesFile = fopen(sourcesFilePath, "r");
    if (!sourcesFile)
        return errno;

    FILE* resultsFile = fopen(resultsFilePath, "w");
    if (!resultsFile) {
        fclose(sourcesFile);
        return errno;
    }

    DoublyLinkedList* sequence = createNewDoublyLinkedList();

    fscanf(sourcesFile, "%d\n", &sequenceSize);
    for (int i = 0; i < sequenceSize; i++) {
        appendElement(sequence, createNewElement(fgetc(sourcesFile)));
    }
    fscanf(sourcesFile, "%d\n", &numberOfLines);
    for (int i = 0; i < numberOfLines; i++) {
        fscanf(sourcesFile, "%s %s %s\n", currentCommand, firstArgument, secondArgument);
        if (strcmp(currentCommand, "INSERT") == 0 && !insertFragment(sequence, firstArgument, secondArgument)) {
            fclose(resultsFile);
            fclose(sourcesFile);
            deleteDoublyLinkedList(sequence);
            return INSERTION_ERROR;
        }
        if (strcmp(currentCommand, "REPLACE") == 0 && !replaceFragment(sequence, firstArgument, secondArgument)) {
            fclose(resultsFile);
            fclose(sourcesFile);
            deleteDoublyLinkedList(sequence);
            return REPLACEMENT_ERROR;
        }
        if (strcmp(currentCommand, "DELETE") == 0 && !deleteFragment(sequence, firstArgument, secondArgument)) {
            fclose(resultsFile);
            fclose(sourcesFile);
            deleteDoublyLinkedList(sequence);
            return DELETION_ERROR;
        }
        for (DoublyLinkedListElement* currentElement = getHead(sequence); currentElement; currentElement = getNextElement(currentElement)) {
            fprintf(resultsFile, "%c", getSymbol(currentElement));
        }
        fprintf(resultsFile, "\n");
    }

    fclose(resultsFile);
    fclose(sourcesFile);
    deleteDoublyLinkedList(sequence);
    return 0;
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        printf("CONSOLE INPUT FORMAT VIOLATION!");
        return 0;
    }
    int resultCode = recoverDNA(argv[1], argv[2]);
    if (resultCode > 0)
        printf("FILE OPENING ERROR! The error's code (errno):\t%d\n", errno);
    if (resultCode == DELETION_ERROR)
        printf("DELETION ERROR!\n");
    if (resultCode == INSERTION_ERROR)
        printf("INSERTION ERROR!\n");
    if (resultCode == REPLACEMENT_ERROR)
        printf("REPLACEMENT ERROR!\n");
}