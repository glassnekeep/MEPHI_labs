#include <stdio.h>
#include <math.h>

int main() {
    double X;
    double e;
    int previous_factorial = 1;
    printf("Please enter e\n");
    scanf_s("%lf", &e);
    printf("Please enter X\n");
    scanf_s("%lf", &X);
    X = fabs(X);
    double currentPow = 1;
    double multiple = (X / 2) * (X / 2) * (X / 2);
    double S = 0.5;
    int i = 1;
    double current = S;
    double previous = 0;
    do {
        previous = current;
        currentPow *= multiple;
        current = (currentPow) / (i * previous_factorial * 2);
        S += current;
        previous_factorial *= i;
        i++;
    } while(fabs(current - previous) > e);
    printf("The sum of this series with these parameters is equal to %f", S);
    return 0;
}
