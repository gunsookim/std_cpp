//
//  main.cpp
//  c_practice
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    int time;
    scanf("%d", &time);
    // printf("%02d:%02d:%02d\n", time/(60*60), (time%(60*60))/60, time%60 );
    printf("%d:%d:%d\n", time/(60*60), (time%(60*60))/60, time%60 );
    return 0;
}
