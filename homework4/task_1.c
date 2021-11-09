#include "../library/binaryIntegers/binaryIntegers.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int size = 16;
    int firstNumber = 0;
    int secondNumber = 0;
    bool* firstNumberBinary = calloc(size, sizeof(int));
    bool* secondNumberBinary = calloc(size, sizeof(int));
    bool* additionResultBinary = calloc(size, sizeof(int));

    printf("Please, input the first number:\n");
    scanf("%i", &firstNumber);
    printf("Please, input the second number:\n");
    scanf("%i", &secondNumber);

    getBinaryForm(firstNumber, firstNumberBinary);
    getBinaryForm(secondNumber, secondNumberBinary);

    printf("\nThe first binary number:\n");
    for (int i = 0; i < size; i++)
        printf("%d", firstNumberBinary[i]);
    printf("\nThe second binary number:\n");
    for (int i = 0; i < size; i++)
        printf("%d", secondNumberBinary[i]);

    addBinaryNumbers(firstNumberBinary, secondNumberBinary, additionResultBinary);

    printf("\nBinary ddition result:\n");
    for (int i = 0; i < size; i++)
        printf("%d", additionResultBinary[i]);

    printf("\nDecimal addition result:\n%d", getDecimalForm(additionResultBinary));

    free(firstNumberBinary);
    free(secondNumberBinary);
    free(additionResultBinary);
}
