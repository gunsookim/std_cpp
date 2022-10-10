//
//  checkNum.cpp
//  c_practice//

#include <stdio.h>

int main(){
    int N;
    int score = 0;
    scanf("%d", &N);
    for(int i = 1; i <= N; i++){
        if((i%10) == 3){
            score++;
        }
        if((i/10) == 3){
            score++;
        }
    }
    printf("%d", score);
    return 0;
}
