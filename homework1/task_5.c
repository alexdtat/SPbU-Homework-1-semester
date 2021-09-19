#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void spiralFilling(int** array, bool** wasChanged, int arraySideSize)
{
    int direction = 0;
    int xPosition = arraySideSize / 2;
    int yPosition = arraySideSize / 2;
    int currentElement = 1;
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};

    while (currentElement <= arraySideSize * arraySideSize) {
        array[yPosition][xPosition] = currentElement++;
        wasChanged[yPosition][xPosition] = true;
        yPosition += dy[direction % 4];
        xPosition += dx[direction % 4];

        if (!wasChanged[yPosition + dy[(direction + 1) % 4]][xPosition + dx[(direction + 1) % 4]])
            direction++;
    }
}

int main()
{
    int n = 0;

    printf("%s", "Please, input the number n:\n");
    scanf("%d", &n);

    int** array;
    array = (int**)calloc(n, sizeof(int*));
    bool** wasChanged;
    wasChanged = (bool**)calloc(n, sizeof(bool*));

    for (int i = 0; i < n; i++) {
        array[i] = (int*)calloc(n, sizeof(int));
        wasChanged[i] = (bool*)calloc(n, sizeof(bool));
    }

    spiralFilling(array, wasChanged, n);

    printf("%s", "Array:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d %c", array[i][j], ' ');
        }
        printf("%c", '\n');
    }


    for (int i = 0; i < n; i++) {
        free(array[i]);
        free(wasChanged[i]);
    }

    free(array);
    free(wasChanged);
    return 0;
}
