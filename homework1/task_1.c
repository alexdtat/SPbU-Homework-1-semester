#include <math.h>
#include <stdio.h>

void divisionWithRemainder(int a, int b)
{
    int quotient = 0;
    int remainder = 0;
    int temporaryA = abs(a);
    int temporaryB = abs(b);

    while (temporaryA >= temporaryB) {
        temporaryA -= temporaryB;
        ++quotient;
    }
    if (a < 0)
        quotient = -quotient - 1;
    if (b < 0)
        quotient = -quotient;
    remainder = a - quotient * b;

    printf("%d %c %d %c %d %c %d %c", a, '/', b, '=', quotient, '(', remainder, ')');
}

int main()
{
    int numberA = 0;
    int numberB = 0;

    printf("%s", "Please, enter the number a:\n");
    scanf("%d", &numberA);
    printf("%s", "Please, enter the number b:\n");
    scanf("%d", &numberB);

    divisionWithRemainder(numberA, numberB);
    return 0;
}