#include "../library/binaryIntegers/binaryIntegers.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int size = 16;
    int firstNumber = 0;
    int secondNumber = 0;
    _Bool* firstNumberBinary = calloc(size, sizeof(_Bool));
    _Bool* secondNumberBinary = calloc(size, sizeof(_Bool));
    _Bool* additionResultBinary = calloc(size, sizeof(_Bool));

    printf("Please, input the first number:\n");
    scanf("%i", &firstNumber);
    printf("Please, input the second number:\n");
    scanf("%i", &secondNumber);

    getBinaryForm(firstNumber, firstNumberBinary, size);
    getBinaryForm(secondNumber, secondNumberBinary, size);

    printf("\nThe first binary number:\n");
    for (int i = 0; i < size; i++)
        printf("%d", firstNumberBinary[i]);
    printf("\nThe second binary number:\n");
    for (int i = 0; i < size; i++)
        printf("%d", secondNumberBinary[i]);

    addBinaryNumbers(firstNumberBinary, secondNumberBinary, additionResultBinary, size);

    printf("\nBinary ddition result:\n");
    for (int i = 0; i < size; i++)
        printf("%d", additionResultBinary[i]);

    printf("\nDecimal addition result:\n%d", getDecimalForm(additionResultBinary, size));

    free(firstNumberBinary);
    free(secondNumberBinary);
    free(additionResultBinary);
}
