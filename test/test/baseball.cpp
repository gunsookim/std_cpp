//
//  baseball.cpp
//  c_practice
//

#include <stdio.h>

int main(){
    int a, b, c;
    int x, y, z;
    int n = 0;
    int m = 0;
    scanf("%d %d %d", &a, &b, &c);
    scanf("%d %d %d", &x, &y, &z);
    if(a == x){
        n++;
    }
    else if (a == y || a == z){
        m++;
    }
    if(b == y){
        n++;
    }
    else if (b == x || b == z){
        m++;
    }
    if(c == z){
        n++;
    }
    else if (c == y || c == x){
        m++;
    }
    printf("%dS%dB", n, m);
    return 0;
}
