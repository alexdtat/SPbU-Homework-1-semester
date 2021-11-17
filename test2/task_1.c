#include <stdbool.h>
#include <stdio.h>

/*void matrixMultiplication(long long** matrix[2][2], long long** resultMatrix[2][2]) {
    long long bufferMatrix[2][2] = {0};
    resultMatrix[0][0] =
}*/

void multiplyMatrix(unsigned long long left[2][2], unsigned long long right[2][2])
{
    unsigned long long x = left[0][0] * right[0][0] + left[0][1] * right[1][0];
    unsigned long long y = left[0][0] * right[0][1] + left[0][1] * right[1][1];
    unsigned long long z = left[1][0] * right[0][0] + left[1][1] * right[1][0];
    unsigned long long w = left[1][0] * right[0][1] + left[1][1] * right[1][1];

    left[0][0] = x;
    left[0][1] = y;
    left[1][0] = z;
    left[1][1] = w;
}

void powerMatrix(unsigned long long current[2][2], int power)
{
    unsigned long long iterationMultiplier[2][2] = { { 1, 1 }, { 1, 0 } };

    // n - 1 times multiply the
    // matrix to {{1,0},{0,1}}
    for (int i = 2; i <= power; i++)
        multiplyMatrix(current, iterationMultiplier);
}

unsigned long long fibonacci(int index, bool* error)
{
    unsigned long long fibonacciNumbers[2][2] = { { 1, 1 }, { 1, 0 } };

    if (index < 0 || index > 90) {
        *error = true;
        return -1;
    }

    *error = false;

    if (index == 0)
        return 0;

    powerMatrix(fibonacciNumbers, index - 1);

    return fibonacciNumbers[0][0];
}

int main()
{
    int index = 0;
    bool error = false;
    unsigned long long result = 0;
    printf("Enter your index for Fibonacci number:\n");
    scanf("%d", &index);

    result = fibonacci(index, &error);
    if (error)
        printf("This index i too large!");
    else
        printf("F_%d = %llu", index, result);

    return 0;
}
