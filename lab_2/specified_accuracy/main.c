#include <stdio.h>
#include <math.h>

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
    double S = 2 + pow(x / 2, 1);
    int i = 1;
    double current = S;
    double previous = 0;
    do {
        previous = current;
        current = ((i * previous_factorial * 2) + pow(personalAbs(x) / 2,i + 2 * i));
        S += current;
        previous_factorial *= i;
        i++;
    } while(personalAbs(current - previous) > e);
    printf("The sum of this series with these parameters is equal to %f", S);
    return 0;
}
