#include "../library/mergeSort/mergeSort.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int size = 0;

    printf("Please, enter your array's size:\n");
    scanf("%d", &size);

    int* array = calloc(size, sizeof(int));

    printf("Please, enter your array:\n");
    for (int i = 0; i < size; i++)
        scanf("%d", &array[i]);

    mergeSort(array, size);

    printf("Sorted array:\n");
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);

    free(array);
}