#include <math.h>
#include <stdbool.h>
#include <stdio.h>

void getScientificNotation(const double number, bool* isNotNegative, double* mantissa, int* exponent)
{
    *exponent = 0;
    *isNotNegative = number >= 0;
    *mantissa = fabs(number);

    while (*mantissa >= 2) {
        *mantissa /= 2;
        *exponent += 1;
    }

    while (*mantissa < 1) {
        *mantissa *= 2;
        *exponent -= 1;
    }
}

int main()
{
    double number = 0;
    printf("Please, enter your double number:\n");
    scanf("%lf", &number);

    bool isNotNegative = false;
    double mantissa = 0;
    int exponent = 0;

    getScientificNotation(number, &isNotNegative, &mantissa, &exponent);

    printf("The scientific notation:\n");
    if (isNotNegative)
        printf("%f=%f*2^%d", number, mantissa, exponent);
    else
        printf("%f=-%f*2^%d", number, mantissa, exponent);
}