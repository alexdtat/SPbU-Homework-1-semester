#include <stdio.h>
#include <stdlib.h>

void swapSectionsOfArray(int* array, int size, int sectionSize)
{
    int sectionBegin = 0;
    int buffer = 0;

    while (sectionBegin + 2 * sectionSize < size) {
        for (int curPos = sectionBegin; curPos < sectionBegin + sectionSize; curPos++) {
            buffer = array[curPos];
            array[curPos] = array[sectionSize + curPos];
            array[sectionSize + curPos] = buffer;
        }
        sectionBegin += sectionSize;
    }

    for (int curPos = sectionBegin + sectionSize; curPos < size; curPos++) {
        for (int shiftedPos = sectionBegin + sectionSize; shiftedPos > sectionBegin; shiftedPos--) {
            buffer = array[shiftedPos];
            array[shiftedPos] = array[shiftedPos - 1];
            array[shiftedPos - 1] = buffer;
        }
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
