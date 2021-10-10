#include <math.h>
#include <stdio.h>

void inverse(_Bool* numberBinary)
{
    for (int i = 0; i < 16; i++)
        numberBinary[i] = !numberBinary[i];
}

void increment(_Bool* numberBinary)
{
    _Bool shouldBeInversed = 1;
    for (int i = 15; i >= 0 && shouldBeInversed; i--) {
        numberBinary[i] = !numberBinary[i];
        shouldBeInversed = !(numberBinary[i]);
    }
}

void getBinaryForm(int number, _Bool* numberBinary)
{
    _Bool sign = (number >= 0);
    number = abs(number);
    for (int i = 0; number != 0; i++) {
        numberBinary[15 - i] = number % 2;
        number /= 2;
    }

    if (!sign) {
        inverse(numberBinary);
        increment(numberBinary);
    }
}

int getDecimalForm(_Bool* numberBinary)
{
    int numberDecimal = 0;
    int factor = 0;
    _Bool sign = 1;
    _Bool copy[16] = { 0 };
    for (int i = 0; i < 16; i++)
        copy[i] = numberBinary[i];

    if (copy[0]) {
        sign = 0;
        inverse(copy);
    }

    for (int i = 15; i >= 0; i--) {
        factor = 1;
        for (int j = 0; copy[i] && (j < 15 - i); j++)
            factor *= 2;
        numberDecimal += copy[i] * factor;
    }
    if (!sign)
        return -numberDecimal - 1;
    else
        return numberDecimal;
}

void addBinaryNumbers(_Bool* firstNumber, _Bool* secondNumber, _Bool* result)
{
    _Bool shouldBeReversed = 0;
    for (int i = 15; i >= 0; i--) {
        result[i] = ((firstNumber[i] != secondNumber[i]) != shouldBeReversed);
        shouldBeReversed = (firstNumber[i] & secondNumber[i]) | ((firstNumber[i] | secondNumber[i]) & shouldBeReversed);
    }
}

int main()
{
    int firstNumber = 0;
    int secondNumber = 0;
    _Bool firstNumberBinary[16] = { 0 };
    _Bool secondNumberBinary[16] = { 0 };
    _Bool additionResultBinary[16] = { 0 };

    printf("Please, input the first number:\n");
    scanf("%i", &firstNumber);
    printf("Please, input the second number:\n");
    scanf("%i", &secondNumber);

    getBinaryForm(firstNumber, firstNumberBinary);
    getBinaryForm(secondNumber, secondNumberBinary);

    printf("\nThe first binary number:\n");
    for (int i = 0; i < 16; i++)
        printf("%d", firstNumberBinary[i]);
    printf("\nThe second binary number:\n");
    for (int i = 0; i < 16; i++)
        printf("%d", secondNumberBinary[i]);

    addBinaryNumbers(firstNumberBinary, secondNumberBinary, additionResultBinary);

    printf("\nBinary ddition result:\n");
    for (int i = 0; i < 16; i++)
        printf("%d", additionResultBinary[i]);

    printf("\nDecimal addition result:\n%d", getDecimalForm(additionResultBinary));
    return 0;
}
