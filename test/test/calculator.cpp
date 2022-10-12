//
//  calculator.cpp
//  c_practice
//

#include <stdio.h>

int main(void){
    int a, b, result;
    char cal;
    printf("수식을 입력하시오.\n");
    scanf("%d %c %d", &a, &cal, &b);
    switch(cal){
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            result = a / b;
            break;
        case '%':
            result = a % b;
            break;
        default:
            result = 0;
            printf("지원하지 않는 연산자입니다.");
            break;
    }
    printf("%d %c %d = %d \n", a, cal, b, result);
    return 0;
}
