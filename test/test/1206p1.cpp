//
//  1206p1.cpp
//  c_practice
//

#include <stdio.h>

int main(void) {
    // your code goes here
    int n[5] = {};
    double avg=0;
    int ln[5] = {};
    int score = 0;
    for(int i = 0; i<5; i++){
        scanf("%d", &n[i]);
    }
    for(int i = 0; i<5; i++){
        avg += n[i];
    }
    avg /= 5;
    
    for(int i = 0 ; i<5; i++){
        if(avg < n[i]){
            printf("%d ", n[i]);
        }
    }
    return 0;
}
