//
// Created by Алексей on 14.12.2021.
//

#ifndef INC_14_12_2021_COMPLEXNUMBER_H
#define INC_14_12_2021_COMPLEXNUMBER_H

typedef struct ComplexNumber {
    double realPart;
    double imaginaryPart;
} ComplexNumber;

ComplexNumber getComplexNumber(double realPart, double imaginaryPart);
ComplexNumber multiplyComplexNumbers(ComplexNumber number1, ComplexNumber number2);
ComplexNumber addComplexNumbers(ComplexNumber number1, ComplexNumber number2);
ComplexNumber subtractComplexNumbers(ComplexNumber number1, ComplexNumber number2);
ComplexNumber divideComplexNumbers(ComplexNumber number1, ComplexNumber number2);
double calculateModule(ComplexNumber number);
void printComplexNumber(ComplexNumber number);

#endif // INC_14_12_2021_COMPLEXNUMBER_H
