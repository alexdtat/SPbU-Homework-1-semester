#include "mergeSort.h"
#include <stdlib.h>

void mergeSortInRange(int* array, int leftBound, int rightBound)
{
    if (leftBound == rightBound)
        return;

    int separator = (leftBound + rightBound) / 2;
    int leftPosition = leftBound;
    int rightPosition = separator + 1;

    mergeSortInRange(array, leftPosition, separator);
    mergeSortInRange(array, rightPosition, rightBound);

    int* buffer = calloc(rightBound - leftBound + 1, sizeof(int));

    for (int shiftedPosition = 0; shiftedPosition < rightBound - leftBound + 1; shiftedPosition++) {
        if ((rightPosition > rightBound) || ((leftPosition <= separator) && (array[leftBound] < array[rightPosition])))
            buffer[shiftedPosition] = array[leftPosition++];
        else
            buffer[shiftedPosition] = array[rightPosition++];
    }

    for (int shift = 0; shift < rightBound - leftBound + 1; shift++)
        array[leftBound + shift] = buffer[shift];

    free(buffer);
}

void mergeSort(int* array, int size)
{
    mergeSortInRange(array, 0, size - 1);
}
