//
//  1213p2.cpp
//  c_practice
//

#include <stdio.h>
int main(void) {
    int n[20];
    int c = 0;
    for(int i = 0; i < 20; i++){
        scanf("%d", n + i);
        if(*(n+i) == 0){
            c = i;
            break;
        }
    }
    for(int i = c-1; i >= 0 ; i--){
        printf("%d", *(n + i));
    }
    return 0;
}
