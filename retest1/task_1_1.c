#include "../library/ComplexNumber/ComplexNumber.h"
#include <stdio.h>

int main()
{
    double firstReal = 0;
    double firstImaginary = 0;
    double secondReal = 0;
    double secondImaginary = 0;
    printf("Please, input first complex number (two float numbers):\n");
    scanf("%lf %lf", &firstReal, &firstImaginary);
    printf("Please, input second complex number (two float numbers):\n");
    scanf("%lf %lf", &secondReal, &secondImaginary);

    ComplexNumber number1 = getComplexNumber(firstReal, firstImaginary);
    ComplexNumber number2 = getComplexNumber(secondReal, secondImaginary);

    printf("Numbers:\n");
    printComplexNumber(number1);
    printf("\n");
    printComplexNumber(number2);

    printf("\nSum:\t");
    printComplexNumber(addComplexNumbers(number1, number2));
    printf("\nSubtraction:\t");
    printComplexNumber(subtractComplexNumbers(number1, number2));
    printf("\nMultiplication:\t");
    printComplexNumber(multiplyComplexNumbers(number1, number2));
    printf("\nDivision:\t");
    printComplexNumber(divideComplexNumbers(number1, number2));
    printf("\nFirst module:\t%lf\nSecond module:\t%lf", calculateModule(number1), calculateModule(number2));
    return 0;
}
