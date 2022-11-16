//
//  1114p1.cpp
//  c_practice
//

#include<stdio.h>

int main() {
    int a, b;
    long as, bs;
    scanf("%d", &a);
    scanf("%d", &b);
    as = a * a;
    bs = b * b;
    if (as == b) {
        printf("%d*%d=%d\n", a, a, b);
    }
    else if (bs == a) {
        printf("%d*%d=%d\n", b, b, a);
    }
    else {
        printf("none\n");
    }
    return 0;
}
