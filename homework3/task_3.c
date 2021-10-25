#include "../library/binaryIntegers/binaryIntegers.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    const int size = 16;
    int firstNumber = 0;
    int secondNumber = 0;
    int result = 0;
    _Bool* firstNumberBinary = calloc(size, sizeof(_Bool));
    _Bool* secondNumberBinary = calloc(size, sizeof(_Bool));
    _Bool* resultBinary = calloc(size, sizeof(_Bool));

    printf("Please, enter the first number:\n");
    scanf("%d", &firstNumber);
    printf("Please, enter the second number:\n");
    scanf("%d", &secondNumber);

    getBinaryForm(firstNumber, firstNumberBinary, size);
    getBinaryForm(secondNumber, secondNumberBinary, size);

    multiplyBinaryNumbers(firstNumberBinary, secondNumberBinary, resultBinary, size);
    result = getDecimalForm(resultBinary, size);

    printf("\n%d * %d = %d", firstNumber, secondNumber, result);

    free(firstNumberBinary);
    free(secondNumberBinary);
    free(resultBinary);
}