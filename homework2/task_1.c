#include "../library/LinkedMap/LinkedMap.h"
#include <errno.h>
#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void readFileIntoLinkedMap(LinkedMap* map, const char* filePath)
{
    FILE* sourcesFile = NULL;
    char bufferString[128];
    errno = 0;

    sourcesFile = fopen(filePath, "r");

    if (sourcesFile) {
        while (fscanf(sourcesFile, "%s ", bufferString) != EOF)
            put(map, bufferString, get(map, bufferString) + 1);
        fclose(sourcesFile);
    } else
        printf("FILE OPENING ERROR! The error's code (errno):\t%d\n", errno);
}

void writeLinkedMapIntoFile(LinkedMap* map, const char* filePath)
{
    FILE* resultsFile = NULL;
    errno = 0;

    resultsFile = fopen(filePath, "w");

    if (resultsFile) {
        for (LinkedMapElement* mapElement = getHead(map); mapElement; mapElement = getNextElement(mapElement)) {
            fprintf(resultsFile, "%s,%d\n", getKey(mapElement), getValue(mapElement));
        }
        fclose(resultsFile);
    } else
        printf("FILE OPENING ERROR! The error's code (errno):\t%d\n", errno);
}

int main(int argc, char* argv[])
{
    if (argc == 3) {
        setlocale(LC_ALL, "Russian");
        char sourcesFilePath[256];
        char resultsFilePath[256];

        strcpy(sourcesFilePath, argv[1]);
        strcpy(resultsFilePath, argv[2]);

        LinkedMap* myMap = createNewLinkedMap();

        readFileIntoLinkedMap(myMap, sourcesFilePath);
        writeLinkedMapIntoFile(myMap, resultsFilePath);

        deleteLinkedMap(myMap);
    } else
        printf("CONSOLE INPUT FORMAT VIOLATION!");
    return 0;
}
