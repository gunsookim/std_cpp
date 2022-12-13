//
//  1213p1.cpp
//  c_practice
//

#include <stdio.h>
int main(void) {
    int x, y, z;
    int* px = &x;
    int* py = &y;
    int* pz = &z;
    int* tmp;
    tmp = px;
    px = pz;
    pz = py;
    py = tmp;
    scanf("%d %d %d", &x, &y, &z);
    printf("%d %d %d", *px, *py, *pz);
    
    return 0;
}
