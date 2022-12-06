//
//  1206p3.cpp
//  c_practice
//

#include <stdio.h>

int main(void) {
    // your code goes here
    char n[5];
    for(int i=0;i<5;i++){
        scanf("%c",&n[i]);
    }
    for(int i=0;i<5;i++){
        printf("%c",n[i]);
    }
        printf("\n");
    for(int i=4;i>0;i--){
        for(int j=5-i;j<5;j++){
            printf("%c",n[j]);
        }
        for(int k=0;k<5-i;k++){
            printf("%c",n[k]);
        }
        printf("\n");
    }
    return 0;
}
