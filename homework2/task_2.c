#include "../library/DoublyLinkedList/DoublyLinkedList.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

DoublyLinkedListElement* findFirstOccurrenceSince(const char* searchedSequence, DoublyLinkedListElement* start)
{
    DoublyLinkedListElement* elementOfSequence = NULL;
    bool isSequenceBeginning = true;

    for (DoublyLinkedListElement* currentElement = start; currentElement; currentElement = getNextElement(currentElement)) {
        if (getSymbol(currentElement) == searchedSequence[0]) {
            isSequenceBeginning = true;
            elementOfSequence = currentElement;
            for (int i = 0; i < strlen(searchedSequence) && elementOfSequence && isSequenceBeginning; i++) {
                if (getSymbol(elementOfSequence) != searchedSequence[i])
                    isSequenceBeginning = false;
                if ((i == strlen(searchedSequence) - 1) && isSequenceBeginning)
                    return currentElement;
                elementOfSequence = getNextElement(elementOfSequence);
            }
        }
    }

    return NULL;
}

DoublyLinkedListElement* goToEndOfFirstOccurrenceSince(const char* sequence, DoublyLinkedListElement* start)
{
    DoublyLinkedListElement* currentPosition = NULL;

    currentPosition = findFirstOccurrenceSince(sequence, start);
    for (int i = 0; i < strlen(sequence) - 1; i++)
        currentPosition = getNextElement(currentPosition);

    return currentPosition;
}

void insertFragmentAfterElement(DoublyLinkedList* list, DoublyLinkedListElement* elementBefore, const char* fragment)
{
    DoublyLinkedListElement* currentPosition = elementBefore;

    for (int i = 0; i < strlen(fragment); i++) {
        insertElementAfter(list, createNewElement(fragment[i]), currentPosition);
        currentPosition = getNextElement(currentPosition);
    }
}

void deleteFragmentInRange(DoublyLinkedList* list, DoublyLinkedListElement* startingElement, DoublyLinkedListElement* elementAfter)
{
    for (DoublyLinkedListElement* currentPosition = startingElement; currentPosition != elementAfter; currentPosition = deleteElementAndGetNext(list, currentPosition)) { }
}

void insertFragment(DoublyLinkedList* list, const char* start, const char* fragment)
{
    DoublyLinkedListElement* currentPosition = goToEndOfFirstOccurrenceSince(start, getHead(list));

    insertFragmentAfterElement(list, currentPosition, fragment);
}

void deleteFragment(DoublyLinkedList* list, const char* start, const char* end)
{
    DoublyLinkedListElement* startingPosition = findFirstOccurrenceSince(start, getHead(list));
    DoublyLinkedListElement* endingPosition = getNextElement(goToEndOfFirstOccurrenceSince(end, getNextElement(goToEndOfFirstOccurrenceSince(start, getHead(list)))));

    deleteFragmentInRange(list, startingPosition, endingPosition);
}

void replaceFragment(DoublyLinkedList* list, const char* template, const char* fragment)
{
    DoublyLinkedListElement* startingPosition = findFirstOccurrenceSince(template, getHead(list));
    DoublyLinkedListElement* elementBeforeStart = getPreviousElement(startingPosition);
    DoublyLinkedListElement* endingPosition = getNextElement(goToEndOfFirstOccurrenceSince(template, getHead(list)));

    deleteFragmentInRange(list, startingPosition, endingPosition);
    insertFragmentAfterElement(list, elementBeforeStart, fragment);
}

void readFileIntoDoublyLinkedListAndWriteIntoOther(const char* sourcesFilePath, const char* resultsFilePath, DoublyLinkedList* sequence)
{
    FILE* sourcesFile = NULL;
    FILE* resultsFile = NULL;
    char currentCommand[8];
    char firstArgument[128];
    char secondArgument[128];
    int sequenceSize = 0;
    int numberOfLines = 0;
    errno = 0;

    sourcesFile = fopen(sourcesFilePath, "r");

    if (sourcesFile) {
        resultsFile = fopen(resultsFilePath, "w");
        if (resultsFile) {
            fscanf(sourcesFile, "%d\n", &sequenceSize);
            for (int i = 0; i < sequenceSize; i++) {
                appendElement(sequence, createNewElement(fgetc(sourcesFile)));
            }
            fscanf(sourcesFile, "%d\n", &numberOfLines);
            for (int i = 0; i < numberOfLines; i++) {
                fscanf(sourcesFile, "%s %s %s\n", currentCommand, firstArgument, secondArgument);
                if (strcmp(currentCommand, "INSERT") == 0)
                    insertFragment(sequence, firstArgument, secondArgument);
                if (strcmp(currentCommand, "REPLACE") == 0)
                    replaceFragment(sequence, firstArgument, secondArgument);
                if (strcmp(currentCommand, "DELETE") == 0)
                    deleteFragment(sequence, firstArgument, secondArgument);
                for (DoublyLinkedListElement* currentElement = getHead(sequence); currentElement; currentElement = getNextElement(currentElement)) {
                    fprintf(resultsFile, "%c", getSymbol(currentElement));
                }
                fprintf(resultsFile, "\n");
            }

            fclose(resultsFile);
        } else
            printf("RESULTS FILE OPENING ERROR! The error's code (errno):\t%d\n", errno);

        fclose(sourcesFile);
    } else
        printf("SOURCES FILE OPENING ERROR! The error's code (errno):\t%d\n", errno);
}

int main(int argc, char* argv[])
{
    if (argc == 3) {
        DoublyLinkedList* sequence = NULL;
        sequence = createNewDoublyLinkedList();
        char sourcesFilePath[256];
        char resultsFilePath[256];
        strcpy(sourcesFilePath, argv[1]);
        strcpy(resultsFilePath, argv[2]);

        readFileIntoDoublyLinkedListAndWriteIntoOther(sourcesFilePath, resultsFilePath, sequence);

        deleteDoublyLinkedList(sequence);
    } else
        printf("CONSOLE INPUT FORMAT VIOLATION!");
}