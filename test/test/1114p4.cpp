//
//  1114p4.cpp
//  c_practice
//

#include<stdio.h>

int main() {
    int n, m;
    long sum;
    scanf("%d", &n);
    scanf("%d", &m);
    if (n == 1) {
        printf("Americano\n");
        sum = m - 500;
    }
    else if (n == 2) {
        printf("Cafe Latte\n");
        sum = m - 400;
    }
    else if (n == 3) {
        printf("Lemon Tea\n");
        sum = m - 300;
    }
    if (sum >= 500) {
        printf("%d %d\n", 1, (sum-500) / 100);
    }
    return 0;
}
