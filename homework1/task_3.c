#include <stdio.h>
#include <stdlib.h>

void swapElementsOfArray(int* array, int firstElementPosition, int secondElementPosition)
{
    int buffer = array[firstElementPosition];
    array[firstElementPosition] = array[secondElementPosition];
    array[secondElementPosition] = buffer;
}

void swapSectionsOfArray(int* array, int size, int sectionSize)
{
    int sectionBegin = 0;

    while (sectionBegin + 2 * sectionSize < size) {
        for (int currentPosition = sectionBegin; currentPosition < sectionBegin + sectionSize; currentPosition++)
            swapElementsOfArray(array, currentPosition, sectionSize + currentPosition);
        sectionBegin += sectionSize;
    }

    for (int currentPosition = sectionBegin + sectionSize; currentPosition < size; currentPosition++) {
        for (int shiftedPosition = sectionBegin + sectionSize; shiftedPosition > sectionBegin; shiftedPosition--)
            swapElementsOfArray(array, shiftedPosition, shiftedPosition - 1);
    }
}

int main()
{
    int size = 0;
    int sectionSize = 0;

    printf("%s", "Please, input the size of the array:\n");
    scanf("%d", &size);
    printf("%s", "Please, input the size of the first section:\n");
    scanf("%d", &sectionSize);

    int* array = calloc(size, sizeof(int));

    printf("%s", "Please, input the array:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &array[i]);
    }

    swapSectionsOfArray(array, size, sectionSize);

    printf("%s", "The processing result:\n");
    for (int i = 0; i < size; i++) {
        printf("%d %c", array[i], ' ');
    }

    free(array);
    return 0;
}
