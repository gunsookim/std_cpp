//
//  1114p2.cpp
//  c_practice

#include<stdio.h>

int main() {
    int a, b, c;
    int max, min;
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);
    if (a>=b && a>=c && b>=c) {
        max = a;
        min = c;
    }
    else if (a >= b && a >= c && b <= c) {
        max = a;
        min = b;
    }
    else if (b >= a && b >= c && a >= c) {
        max = b;
        min = c;
    }
    else if (b >= a && b >= c && c >= a) {
        max = b;
        min = a;
    }
    else if (c >= a && c >= b && a >= b) {
        max = c;
        min = b;
    }
    else if (c >= a && c >= b && b >= a) {
        max = c;
        min = a;
    }

    printf("%d %d\n", max, min);

    return 0;
}
