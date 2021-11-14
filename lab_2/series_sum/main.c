#include <stdio.h>
#include <math.h>

int main() {
    int n;
    double X;
    int previous_factorial = 1;
    printf("Please enter n\n");
    scanf_s("%d", &n);
    printf("Please enter X\n");
    scanf_s("%lf", &X);
    X = fabs(X);
    double S = 2 + pow(X / 2, n);
    for(int i = 1; i <= n; i++) {
        S += i * previous_factorial * 2 + pow(X / 2,  n + 2 * i);
        previous_factorial *= i;
    }
    printf("The sum of this series with these parameters is equal to %f", S);
    return 0;
}
