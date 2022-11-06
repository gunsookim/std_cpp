//
//  structure.cpp
//  c_practice
//
#include <stdio.h>
int LinearSearch(int arr[], int len, int target){
    for(int i = 0; i<len; i++){
        if(arr[i] == target){
            return i;
        }
    }
    return -1;
}
int main(void){
    int arr[] = {1,2,3,4,5};
    int index;
    index = LinearSearch(arr, sizeof(arr)/sizeof(int), 4);
    if(index == -1){
        printf("탐색실패\n");
    }
    else{
        printf("타겟 저장 인덱스: %d \n", index);
    }
    index = LinearSearch(arr, sizeof(arr)/sizeof(int), 7);
    if(index == -1){
        printf("탐색실패\n");
    }
    else{
        printf("타겟 저장 인덱스: %d \n", index);
    }
    return 0;
}
