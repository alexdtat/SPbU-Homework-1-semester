#include "binaryIntegers.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 16

void inverse(bool* numberBinary)
{
    for (int i = 0; i < SIZE; i++)
        numberBinary[i] = !numberBinary[i];
}

void increment(bool* numberBinary)
{
    bool shouldBeInversed = true;
    for (int i = SIZE - 1; i >= 0 && shouldBeInversed; i--) {
        numberBinary[i] = !numberBinary[i];
        shouldBeInversed = !(numberBinary[i]);
    }
}

void getBinaryForm(int number, bool* numberBinary)
{
    bool isPositive = (number >= 0);
    number = abs(number);
    for (int i = 0; number != 0; i++) {
        numberBinary[SIZE - 1 - i] = number % 2;
        number /= 2;
    }

    if (!isPositive) {
        inverse(numberBinary);
        increment(numberBinary);
    }
}

int getDecimalForm(bool* numberBinary)
{
    int numberDecimal = 0;
    int factor = 0;
    bool isPositive = true;
    bool* copy = calloc(SIZE, sizeof(int));
    for (int i = 0; i < SIZE; i++)
        copy[i] = numberBinary[i];

    if (copy[0]) {
        isPositive = false;
        inverse(copy);
    }

    factor = 1;
    for (int i = SIZE - 1; i >= 0; i--) {
        numberDecimal += copy[i] * factor;
        factor *= 2;
    }

    free(copy);

    if (!isPositive)
        return -numberDecimal - 1;
    else
        return numberDecimal;
}

void addBinaryNumbers(bool* firstNumber, bool* secondNumber, bool* result)
{
    bool shouldBeInversed = false;
    int buffer = 0;

    for (int i = SIZE - 1; i >= 0; i--) {
        buffer = ((firstNumber[i] != secondNumber[i]) != shouldBeInversed);
        shouldBeInversed = (firstNumber[i] & secondNumber[i]) | (firstNumber[i] & shouldBeInversed)
            | (secondNumber[i] & shouldBeInversed); // XOR won't be shorter?
        result[i] = buffer;
    }
}

void leftBinaryShift(bool* number)
{
    for (int i = 1; i < SIZE - 1; i++)
        number[i] = number[i + 1];
    number[SIZE - 1] = 0;
}

void multiplyBinaryNumbers(bool* firstNumber, bool* secondNumber, bool* resultNumber)
{
    bool firstIsNotNegative = true;
    bool secondIsNotNegative = true;
    bool resultIsNull = true;

    bool* buffer = calloc(SIZE, sizeof(int));

    getBinaryForm(0, resultNumber);

    if (firstNumber[0]) {
        firstIsNotNegative = false;
        inverse(firstNumber);
        increment(firstNumber);
    }

    if (secondNumber[0]) {
        secondIsNotNegative = false;
        inverse(secondNumber);
        increment(secondNumber);
    }

    memcpy(buffer, firstNumber, SIZE);

    for (int i = SIZE - 1; i > 0; i--) {
        if (secondNumber[i]) {
            addBinaryNumbers(resultNumber, buffer, resultNumber);
            resultIsNull = false;
        }
        leftBinaryShift(buffer);
    }

    if (!resultIsNull && (firstIsNotNegative != secondIsNotNegative)) {
        inverse(resultNumber);
        increment(resultNumber);
    }

    free(buffer);
}