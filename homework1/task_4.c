#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void compositeNumbersSelection(bool* numbersAreComposite, int maxNumber, bool* thereArePrimes)
{
    for (long i = 2; i * i <= maxNumber; i++) {
        *thereArePrimes = true;
        for (long j = 2; i * j <= maxNumber; j++)
            numbersAreComposite[i * j] = true;
    }
}

int main()
{
    int maxNumber = 0;
    bool thereArePrimes = false;

    printf("%s", "Please, input the boundary value:\n");
    scanf("%d", &maxNumber);

    bool* numbersAreComposite = calloc(maxNumber + 1, sizeof(bool));

    compositeNumbersSelection(numbersAreComposite, maxNumber, &thereArePrimes);

    if (thereArePrimes) {
        printf("%s", "Prime numbers not exceeding the boundary value:\n");
        for (int i = 2; i <= maxNumber; i++) {
            if (!numbersAreComposite[i]) {
                printf("%d %c", i, ' ');
            }
        }
    } else {
        printf("%s", "There are no prime numbers not exceeding the boundary value!");
    }

    free(numbersAreComposite);
    return 0;
}
