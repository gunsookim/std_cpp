//
//  1206p2.cpp
//  c_practice
//

#include <stdio.h>

int main(void) {
    // your code goes here
    int n[10];
    int a[3] = {};
    for(int i = 0; i<10; i++){
        scanf("%d", &n[i]);
    }
    for(int i = 0; i<10; i++){
        if(n[i] == 1){
            a[0]++;
        }
        else if(n[i] == 2){
            a[1]++;
        }
        else if(n[i] == 3){
            a[2]++;
        }
    }
    for(int i = 0; i<3; i++){
        printf("%d: ", i +1);
        for(int j = 0; j<a[i]; j++){
            printf("*");
        }
        printf("\n");
    }
    return 0;
}
