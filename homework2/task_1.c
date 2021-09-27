#include "../library/LinkedMap/LinkedMap.h"
#include <errno.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

void readFileIntoLinkedMap(LinkedMap* map, const char* filePath)
{
    FILE* sourcesFile = NULL;
    char* bufferString = NULL;
    errno = 0;

    bufferString = calloc(map->keySize, sizeof(char));
    sourcesFile = fopen(filePath, "r");

    if (sourcesFile) {
        while (fscanf(sourcesFile, "%s ", bufferString) != EOF) {
            if (!hasKey(map, bufferString))
                appendElement(map, createNewElement(bufferString, map->keySize));
            put(map, bufferString, get(map, bufferString) + 1);
            for (int i = 0; bufferString[i] != '\0'; i++)
                bufferString[i] = '\0';
        }
        fclose(sourcesFile);
    } else
        printf("FILE OPENING ERROR! The error's code (errno):\t%d\n", errno);

    free(bufferString);
}

void writeLinkedMapIntoFile(LinkedMap* map, const char* filePath)
{
    FILE* resultsFile = NULL;
    errno = 0;

    resultsFile = fopen(filePath, "w");

    if (resultsFile) {
        for (LinkedMapElement* mapElement = map->head; mapElement != NULL; mapElement = mapElement->nextElement) {
            fprintf(resultsFile, "%s,%d\n", mapElement->key, mapElement->value);
        }
        fclose(resultsFile);
    } else
        printf("FILE OPENING ERROR! The error's code (errno):\t%d\n", errno);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    char* sourcesFilePath = calloc(255, sizeof(char));
    char* resultsFilePath = calloc(255, sizeof(char));

    printf("Please, input the path to the file containing the analyzed text (ANSI or windows-1251 encoding):\n");
    scanf("%s", sourcesFilePath);
    printf("Please, input the path to the file for recording analysis results (ANSI or windows-1251 encoding):\n");
    scanf("%s", resultsFilePath);

    LinkedMap* myMap = createNewLinkedMap();
    resizeLinkedMapElementKey(myMap, 127);

    readFileIntoLinkedMap(myMap, sourcesFilePath);
    writeLinkedMapIntoFile(myMap, resultsFilePath);

    deleteLinkedMap(myMap);
    free(sourcesFilePath);
    free(resultsFilePath);
    return 0;
}
