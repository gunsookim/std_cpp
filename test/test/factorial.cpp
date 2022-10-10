//
//  factorial.cpp
//  c_practice
//

#include <stdio.h>

int main(){
    int N, M;
    int result = 1;
    scanf("%d %d", &M, &N);
    for(int i = M; i <= N; i++){
        printf("%d!=", i);
        for(int j = 1; j <= i; j++){
            result = result * j;
            if(j!=i){
                printf("%d*", j);
            }
            else{
                printf("%d", j);
            }
        }
        printf("=%d", result);
        result = 1;
        printf("\n");
    }
    return 0;
}
