//
//  leap_year.cpp
//  c_practice
//

#include <stdio.h>

int main(){
    int N;
    scanf("%d", &N);if( (((N%4) == 0) && ((N%100) != 0)) || ((N%400) == 0)){
        printf("leap year");
    }
    else{
        printf("common year");
    }
    
    return 0;
}

