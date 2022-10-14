//
//  overflow.cpp
//  c_practice
//

#include <stdio.h>
#include <limits.h>
int main(void){
    short s_num = SHRT_MAX;
    unsigned short u_num = USHRT_MAX;
    printf("short형의 최대 값: %d\n", s_num);
    printf("unsigned short형의 최대 값: %d\n", u_num);
    s_num += 1;
    u_num += 1;
    printf("short형의 overflow (+1): %d\n", s_num);
    printf("unsigned short형의 overflow (+1): %d\n", u_num);
    return 0;
}
