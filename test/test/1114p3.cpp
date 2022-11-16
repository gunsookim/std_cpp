//
//  1114p3.cpp
//  c_practice
//

#include<stdio.h>

int main() {
    int a, b, c;
    double avg;
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);
    avg = (a + b + c) / 3.0;
    if (avg>=91.5) {
        printf("A");
    }
    else if (avg < 91.5 && avg >= 85.5) {
        printf("B");
    }
    else if (avg <= 85.5 && avg >= 80.5) {
        printf("C");
    }
    else {
        printf("F");
    }
    if (a >= 100 || b >= 100 || c >= 100) {
        printf("Good\n");
    }
    if (a < 60 || b < 60 || c < 60) {
        printf("Bad\n");
    }
    return 0;
}
