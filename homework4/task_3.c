#include "../library/binaryIntegers/binaryIntegers.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    const int size = 16;
    int firstNumber = 0;
    int secondNumber = 0;
    int result = 0;
    bool* firstNumberBinary = calloc(size, sizeof(int));
    bool* secondNumberBinary = calloc(size, sizeof(int));
    bool* resultBinary = calloc(size, sizeof(int));

    printf("Please, enter the first number:\n");
    scanf("%d", &firstNumber);
    printf("Please, enter the second number:\n");
    scanf("%d", &secondNumber);

    getBinaryForm(firstNumber, firstNumberBinary);
    getBinaryForm(secondNumber, secondNumberBinary);

    multiplyBinaryNumbers(firstNumberBinary, secondNumberBinary, resultBinary);
    result = getDecimalForm(resultBinary);

    printf("\n%d * %d = %d", firstNumber, secondNumber, result);

    free(firstNumberBinary);
    free(secondNumberBinary);
    free(resultBinary);
}