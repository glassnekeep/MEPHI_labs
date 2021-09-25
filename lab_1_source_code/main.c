#include <stdio.h>
int divisionCheck(int n) {
    int a = n;
    while(a > 0) {
        int b = a % 10;
        if(b == 0) {
            return 1;
        }
        if(n % b != 0) {
            return 2;
        }
        a = a / 10;
    }
    return 0;
}

int main() {
    int n;
    printf("Please enter n\n");
    scanf_s("%d", &n);
    printf("%d\n", n);
    if(n <= 0) {
        printf("There are no such numbers because entered n <= 0\n");
        return 1;
    }
    for(int i = 1; i <= n; i++) {
        if(!divisionCheck(i)) {
            printf("%d ", i);
        }
    }
    return 0;
}