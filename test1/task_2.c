#include "../library/LinkedList/LinkedList.h"
#include "stddef.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>

bool readSourcesFile(const char* sourcesFilePath, int lowerBound, int upperBound, LinkedList* lessThanLower, LinkedList* inRange, LinkedList* greaterThanUpper)
{
    errno = 0;
    FILE* sourcesFile = NULL;
    sourcesFile = fopen(sourcesFilePath, "r");
    if (sourcesFile) {
        int currentNumber = 0;
        while (fscanf(sourcesFile, "%d ", &currentNumber) != EOF) {
            if (currentNumber < lowerBound)
                appendNewElement(lessThanLower, currentNumber);
            if (currentNumber > upperBound)
                appendNewElement(greaterThanUpper, currentNumber);
            if (currentNumber >= lowerBound && currentNumber <= upperBound)
                appendNewElement(inRange, currentNumber);
        }
        fclose(sourcesFile);
        return true;
    } else {
        printf("SOURCES FILE OPENING ERROR! The error's code (errno):\t%d\n", errno);
        return false;
    }
}

bool writeResultsFile(const char* resultsFilePath, LinkedList* lessThanLower, LinkedList* inRange, LinkedList* greaterThanUpper)
{
    errno = 0;
    FILE* resultsFile = NULL;
    resultsFile = fopen(resultsFilePath, "w");
    if (resultsFile) {
        for (LinkedListElement* currentElement = getHead(lessThanLower); currentElement; currentElement = getNextElement(currentElement))
            fprintf(resultsFile, "%d ", getValue(currentElement));
        for (LinkedListElement* currentElement = getHead(inRange); currentElement; currentElement = getNextElement(currentElement))
            fprintf(resultsFile, "%d ", getValue(currentElement));
        for (LinkedListElement* currentElement = getHead(greaterThanUpper); currentElement; currentElement = getNextElement(currentElement))
            fprintf(resultsFile, "%d ", getValue(currentElement));

        fclose(resultsFile);
        return true;
    } else {
        printf("RESULTS FILE OPENING ERROR! The error's code (errno):\t%d\n", errno);
        return false;
    }
}

int main()
{
    char sourcesFilePath[256];
    char resultsFilePath[256];
    int numberA = 0;
    int numberB = 0;
    LinkedList* lessThanLower = createNewLinkedList();
    LinkedList* inRange = createNewLinkedList();
    LinkedList* greaterThanUpper = createNewLinkedList();

    printf("Please, input the sources file's path:\n");
    scanf("%s", sourcesFilePath);
    printf("Please, input number a:\n");
    scanf("%d", &numberA);
    printf("Please, input number b:\n");
    scanf("%d", &numberB);

    if (numberA > numberB)
        printf("ERROR! Number a shouldn't be greater than number b:\n");
    else if (readSourcesFile(sourcesFilePath, numberA, numberB, lessThanLower, inRange, greaterThanUpper))
        writeResultsFile(resultsFilePath, lessThanLower, inRange, greaterThanUpper);

    deleteLinkedList(lessThanLower);
    deleteLinkedList(inRange);
    deleteLinkedList(greaterThanUpper);
    return 0;
}
