#include "../library/LinkedMap/LinkedMap.h"
#include <errno.h>
#include <locale.h>
#include <stddef.h>
#include <stdio.h>

int readFileIntoLinkedMap(LinkedMap* map, const char* filePath)
{
    char bufferString[128];
    errno = 0;
    FILE* sourcesFile = fopen(filePath, "r");

    if (sourcesFile) {
        while (fscanf(sourcesFile, "%s ", bufferString) != EOF)
            put(map, bufferString, get(map, bufferString) + 1);
        fclose(sourcesFile);
    }
    return errno;
}

int writeLinkedMapIntoFile(LinkedMap* map, const char* filePath)
{
    errno = 0;
    FILE* resultsFile = fopen(filePath, "w");

    if (resultsFile) {
        for (LinkedMapElement* mapElement = getHead(map); mapElement; mapElement = getNextElement(mapElement)) {
            fprintf(resultsFile, "%s,%d\n", getKey(mapElement), getValue(mapElement));
        }
        fclose(resultsFile);
    }
    return errno;
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        printf("CONSOLE INPUT FORMAT VIOLATION!");
        return 0;
    }

    setlocale(LC_ALL, "Russian");
    LinkedMap* myMap = createNewLinkedMap();
    int sourcesFileErrorCode = readFileIntoLinkedMap(myMap, argv[1]);
    int resultsFileErrorCode = writeLinkedMapIntoFile(myMap, argv[2]);

    if (sourcesFileErrorCode)
        printf("SOURCES FILE OPENING ERROR! The error's code (errno):\t%d\n", sourcesFileErrorCode);
    if (resultsFileErrorCode)
        printf("RESULTS FILE OPENING ERROR! The error's code (errno):\t%d\n", resultsFileErrorCode);

    deleteLinkedMap(myMap);
}
