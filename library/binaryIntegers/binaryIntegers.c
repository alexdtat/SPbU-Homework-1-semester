#include "binaryIntegers.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void inverse(_Bool* numberBinary, const int size)
{
    for (int i = 0; i < size; i++)
        numberBinary[i] = !numberBinary[i];
}

void increment(_Bool* numberBinary, const int size)
{
    bool shouldBeInversed = true;
    for (int i = size - 1; i >= 0 && shouldBeInversed; i--) {
        numberBinary[i] = !numberBinary[i];
        shouldBeInversed = !(numberBinary[i]);
    }
}

void getBinaryForm(int number, _Bool* numberBinary, const int size)
{
    bool isPositive = (number >= 0);
    number = abs(number);
    for (int i = 0; number != 0; i++) {
        numberBinary[size - 1 - i] = number % 2;
        number /= 2;
    }

    if (!isPositive) {
        inverse(numberBinary, size);
        increment(numberBinary, size);
    }
}

int getDecimalForm(_Bool* numberBinary, const int size)
{
    int numberDecimal = 0;
    int factor = 0;
    bool isPositive = true;
    _Bool* copy = calloc(size, sizeof(_Bool));
    for (int i = 0; i < size; i++)
        copy[i] = numberBinary[i];

    if (copy[0]) {
        isPositive = false;
        inverse(copy, size);
    }

    for (int i = size - 1; i >= 0; i--) {
        factor = 1;
        for (int j = 0; copy[i] && (j < size - 1 - i); j++)
            factor *= 2;
        numberDecimal += copy[i] * factor;
    }

    free(copy);

    if (!isPositive)
        return -numberDecimal - 1;
    else
        return numberDecimal;
}

void addBinaryNumbers(_Bool* firstNumber, _Bool* secondNumber, _Bool* result, const int size)
{
    bool shouldBeInversed = false;
    int buffer = 0;

    for (int i = size - 1; i >= 0; i--) {
        buffer = ((firstNumber[i] != secondNumber[i]) != shouldBeInversed);
        shouldBeInversed = (firstNumber[i] & secondNumber[i]) | ((firstNumber[i] | secondNumber[i]) & shouldBeInversed);
        result[i] = buffer;
    }
}

void leftBinaryShift(_Bool* number, const int size)
{
    for (int i = 1; i < size - 1; i++)
        number[i] = number[i + 1];
    number[size - 1] = 0;
}

void multiplyBinaryNumbers(_Bool* firstNumber, _Bool* secondNumber, _Bool* resultNumber, const int size)
{
    bool firstIsNotNegative = true;
    bool secondIsNotNegative = true;
    bool resultIsNull = true;

    _Bool* buffer = calloc(size, sizeof(_Bool));

    getBinaryForm(0, resultNumber, size);

    if (firstNumber[0]) {
        firstIsNotNegative = false;
        inverse(firstNumber, size);
        increment(firstNumber, size);
    }

    if (secondNumber[0]) {
        secondIsNotNegative = false;
        inverse(secondNumber, size);
        increment(secondNumber, size);
    }

    memcpy(buffer, firstNumber, size);

    for (int i = size - 1; i > 0; i--) {
        if (secondNumber[i]) {
            addBinaryNumbers(resultNumber, buffer, resultNumber, size);
            resultIsNull = false;
        }
        leftBinaryShift(buffer, size);
    }

    if (!resultIsNull && (firstIsNotNegative != secondIsNotNegative)) {
        inverse(resultNumber, size);
        increment(resultNumber, size);
    }

    free(buffer);
}