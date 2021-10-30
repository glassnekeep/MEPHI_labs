#include <stdio.h>

double personalAbs(double a) {
    if(a >= 0) {
        return a;
    } else {
        return (-1) * a;
    }
}

int main() {
    double X;
    double e;
    int previous_factorial = 1;
    printf("Please enter e\n");
    scanf_s("%lf", &e);
    printf("Please enter X\n");
    scanf_s("%lf", &X);
    double x = X > 0 ? X : X * (-1);
    double currentPow = 1;
    double multiple = (x / 2) * (x / 2) * (x / 2);
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
    } while(personalAbs(current - previous) > e);
    printf("The sum of this series with these parameters is equal to %f", S);
    return 0;
}
