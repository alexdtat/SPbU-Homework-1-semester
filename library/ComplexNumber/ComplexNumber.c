#include "ComplexNumber.h"
#include <math.h>
#include <stdio.h>

ComplexNumber getComplexNumber(double realPart, double imaginaryPart)
{
    ComplexNumber result = { realPart, imaginaryPart };
    return result;
}

ComplexNumber multiplyComplexNumbers(ComplexNumber number1, ComplexNumber number2)
{
    double resultRealPart = number1.realPart * number2.realPart - number1.imaginaryPart * number2.imaginaryPart;
    double resultImaginaryPart = number1.realPart * number2.imaginaryPart + number1.imaginaryPart * number2.realPart;
    ComplexNumber result = { resultRealPart, resultImaginaryPart };
    return result;
}

ComplexNumber addComplexNumbers(ComplexNumber number1, ComplexNumber number2)
{
    double resultRealPart = number1.realPart + number2.realPart;
    double resultImaginaryPart = number1.imaginaryPart + number2.imaginaryPart;
    ComplexNumber result = { resultRealPart, resultImaginaryPart };
    return result;
}

ComplexNumber subtractComplexNumbers(ComplexNumber number1, ComplexNumber number2)
{
    double resultRealPart = number1.realPart - number2.realPart;
    double resultImaginaryPart = number1.imaginaryPart - number2.imaginaryPart;
    ComplexNumber result = { resultRealPart, resultImaginaryPart };
    return result;
}

ComplexNumber divideComplexNumbers(ComplexNumber number1, ComplexNumber number2)
{
    ComplexNumber conjugate = { number2.realPart, -number2.imaginaryPart };
    ComplexNumber numerator = multiplyComplexNumbers(number1, conjugate);
    double denominator = multiplyComplexNumbers(number2, conjugate).realPart;
    ComplexNumber result = { numerator.realPart / denominator, numerator.imaginaryPart / denominator };
    return result;
}

double calculateModule(ComplexNumber number)
{
    return sqrt(number.realPart * number.realPart + number.imaginaryPart * number.imaginaryPart);
}

void printComplexNumber(ComplexNumber number)
{
    printf("(%lf) + (%lf) * i", number.realPart, number.imaginaryPart);
}