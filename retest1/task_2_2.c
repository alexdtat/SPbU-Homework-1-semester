#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define START_MODE 0
#define RANDOM_MODE 1
#define CONSOLE_MODE 2

void evenInsertionSort(int size, int *array)
{
    int newElement = 0;
    int position = 0;

    srand(time(NULL));

    for (int i = 1; i < size; i += 2) {
        newElement = array[i];
        position = i - 2;
        while (position >= 0 && array[position] > newElement) {
            array[position + 2] = array[position];
            position = position - 2;
        }
        array[position + 2] = newElement;
    }
}

int main()
{
    int mode = START_MODE;
    int size = 0;
    printf("Please, input array's size:\n");
    scanf("%d", &size);
    int *array = calloc(size, sizeof(int));
    printf("Please, select input mode (1 = random from 11 to 42, 2 = console):\n");
    scanf("%d", &mode);

    if (mode == CONSOLE_MODE) {
        printf("Please, input the array:\n");
        for (int i = 0; i < size; i++)
            scanf("%d", &array[i]);
    }

    if (mode == RANDOM_MODE) {
        for (int i = 0; i < size; i++)
            array[i] = 11 + (rand() % 32);
    }

    printf("\nYour array:\n");
    for (int i = 0; i < size; i++)
        printf("%d\t", array[i]);

    evenInsertionSort(size, array);

    printf("\nThe partially (only even positions are sorted) sorted array:\n");
    for (int i = 0; i < size; i++)
        printf("%d\t", array[i]);

    free(array);
    return 0;
}