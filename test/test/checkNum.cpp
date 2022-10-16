//
//  checkNum.cpp
//  c_practice//

#include <stdio.h>

int main(){
    int n, j;
    int temp, score = 0;
    scanf("%d", &n);
    for(int i=1; i <= n; i++){
        j=i;
        while(j){
            if(j%10 == 3){
                score++;
            }
            j /= 10;
        }
    }
    printf("%d", score);
    return 0;
}
