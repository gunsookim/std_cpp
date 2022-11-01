//
//  1101p4.cpp
//  c_practice
//  2022/11/01_p4

#include <stdio.h>
int main(){
    /*
     영어 소문자 a~z의 아스키 코드 값은 문자 순으로 연속되어있다. 이 성질을 이용하여 입력받은 소문자가 알파벳에서 몇
     번째 문자인지 출력하는 프로그램을 작성하시오. (a는 0번째 문자, z는 25번째 문자로 가정하시오.)
     EX)
     ## Input ##
     b
     ## Output ##
     b는 1번째 영어 소문자
     */
    char a;
    scanf("%c", &a);
    printf("%c는 %d번째 영어 소문자\n", a, a-97);
    return 0;
}
