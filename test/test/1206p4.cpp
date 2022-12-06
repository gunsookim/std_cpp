//
//  1206p4.cpp
//  c_practice
//

#include <stdio.h>

int main(){
    char n[7];
    int p=0;
    for(int i=0;i<7;i++){
        scanf("%c",&n[i]);
    }
    for(int i=0;i<7;i++) {
        if(n[i]=='c'){
            if(n[i+1]=='a'){
                if(n[i+2]=='t'){
                    p++;
                }
            }
        }
    }
    printf("%d",p);
    return 0;
}
