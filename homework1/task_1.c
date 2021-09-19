#include <math.h>
#include <stdbool.h>
#include <stdio.h>

bool divisionWithRemainder(int dividend, int divisor, int* quotient)
{
    int temporaryDividend = abs(dividend);
    int temporaryDivisor = abs(divisor);

    if (divisor == 0)
        return 0;

    while (temporaryDividend >= temporaryDivisor) {
        temporaryDividend -= temporaryDivisor;
        ++(*quotient);
    }
    if (dividend < 0)
        *quotient = -(*quotient) - 1;
    if (divisor < 0)
        *quotient = -(*quotient);

    return 1;
}

int main()
{
    int numberA = 0;
    int numberB = 0;
    int quotient = 0;

    printf("%s", "Please, enter the number a:\n");
    scanf("%d", &numberA);
    printf("%s", "Please, enter the number b:\n");
    scanf("%d", &numberB);

    if (divisionWithRemainder(numberA, numberB, &quotient))
        printf("%d %c %d %c %d", numberA, '/', numberB, '=', quotient);
    else
        printf("%s", "Division by zero is undefined!");
    return 0;
}