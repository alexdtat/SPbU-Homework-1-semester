#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int findMaxPair(int* array, int size, bool* thereExistsMaxPair)
{
    int* maxPair = &array[0];
    for (int i = 0; i < size - 1; i++) {
        if (array[i] > *maxPair || thereExistsMaxPair) {
            for (int j = i + 1; j < size; j++) {
                if (array[j] == array[i]) {
                    *maxPair = array[i];
                    *thereExistsMaxPair = true;
                }
            }
        }
    }

    return *maxPair;
}

int main()
{
    int size = 0;
    int maxPair = 0;
    bool thereExistsMaxPair = false;

    printf("%s", "Please, input the size of the array:\n");
    scanf("%d", &size);

    int* array = calloc(size, sizeof(int));

    printf("%s", "Please, input the array:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &array[i]);
    }

    maxPair = findMaxPair(array, size, &thereExistsMaxPair);

    printf("%s", "The largest number occurring in the array more than 1 time:\n");
    if (thereExistsMaxPair) {
        printf("%d", maxPair);
    } else {
        printf("%s", "There is no such number!");
    }

    free(array);
    return 0;
}
