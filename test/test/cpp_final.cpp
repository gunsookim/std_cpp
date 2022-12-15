#include <stdio.h>

/*
 yyyy년 mm월 1일의 요일을 구하는 함수 get_day를 선언.
 연도와 월에 해당하는 값을 매개변수(int형) yyyy, mm을 통해 함수에 전달.
 반환 타입은 int입니다.
*/
int get_day(int yyyy, int mm);

/*
 yyyy년 mm월의 날 수를 구하는 함수 get_day_of_month를 선언.
 연도와 월에 해당하는 값을 각각 매개변수(int형) yyyy, mm을 통해 함수에 전달.
 반환 타입은 int입니다.
*/
int get_day_of_month(int yyyy, int mm);

/*
 yyyy년이 윤년인지 판별하는 함수 is_leaf_year를 선언.
 연도에 해당하는 값을 매개변수(int형) yyyy를 통해 함수에 전달.
 반환 타입은 int입니다.
*/
int is_leaf_year(int yyyy);

/*
 yyyy년 mm월의 달력(요일과 날짜)를 출력하는 함수 print_cal를 선언.
 yyyy년 mm월 1일의 시작 요일과 일 수에 해당하는 값을 각각 매개변수(int형) start_day, day_num을 통해 함수에 전달.
 반환 타입은 void입니다.
*/
void print_cal(int start_day, int day_num);

//  main 함수
int main(void)
{
    //  int형 변수 yyyy, mm 선언, yyyy, mm 값 입력
    int yyyy, mm; scanf("%d%d",&yyyy, &mm);
    
    /*
     int형으로 선언된 start_day 변수에 호출된 get_day 함수의 반환값 대입.
     get_day에 yyyy, mm이 인수로 전달됨.
     */
    int start_day = get_day(yyyy, mm);
    
    /*
     int형으로 선언된 day_num 변수에 호출된 get_day_of_month 함수의 반환값 대입.
     get_day_of_month 함수에 yyyy, mm이 인수로 전달됨.
     */
    int day_num = get_day_of_month(yyyy, mm);
    /*
     달력 출력 함수인 print_cal 함수 호출.
     start_day, day_num이 인수로 전달됨.
     */
    print_cal(start_day, day_num);
}

//  pirnt_cal 함수 정의
void print_cal(int start_day, int day_num)
{
    //  요일 표시
    printf(" Sun Mon Tue Wed Thu Fri Sat\n");
    //  해당 년월의 1일 요일까지 공백(4칸)을 출력합니다.
    for(int i = 0; i < start_day; i++)
        printf("    ");
    //  시작 요일부터 해당 요일의 날짜를 출력합니다. 요일이 바뀌면 개행을 출력합니다.
    for(int day = 1, ke = start_day; day <= day_num; day++, ke++)
    {
        //  날짜 출력. 공백과 간격을 맞추기 위해 4자리수(%4d)로 출력합니다.
        printf("%4d",day);
        //  ke % == 6인 경우, sat(토요일)이므로 개행을 출력합니다.
        if(ke%7 == 6)
            printf("\n");
    }
}

//  get_day 함수 정의
int get_day(int yyyy, int mm)
{
    //  int형 변수 past 호출 및 0으로 초기화.
    int past = 0;
    
    /*
     기준 일로부터 yyyy년 mm월 1일이 얼마만큼 지났는지는 YYYY년 MM월의 일 수의 누적합이므로,
     (past + 365일(1년) + 윤년으로 인한 추가 날짜)를 계산한뒤 past에 대입합니다.
     */
    for(int y=1; y<yyyy; y++)
        past = past + 365 + is_leaf_year(y);
    /*
     (past + yyyy년 mm월의 일 수)를 계산한뒤 past에 대입합니다.
     */
    for(int m=1; m<mm; m++)
        past = past + get_day_of_month(yyyy, m);
    
    /*
     해당 요일에 대응하는 값을 반환합니다.
     0 == 일요일, 1 == 월요일, 2 == 화요일, 3 == 수요일, 4 == 목요일, 5 == 금요일, 6 == 토요일
     */
    return (1 + past) % 7;
}

// get_day_of_month 함수 정의
int get_day_of_month(int yyyy,  int mm)
{
    //  int형 배열 day_of_month를 월별 날 수에 해당하는 값으로 초기화합니다.
    int day_of_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    /*
     is_leaf_year 함수의 반환값 만큼 day_of_month[2] 값이 증가합니다.
     해당 연도가 윤년인 경우 1이 증가, 아닌경우 증가하지 않음.
     */
    day_of_month[2] += is_leaf_year(yyyy);
    
    //  day_of_month[mm] 값(mm월의 날 수)를 반환합니다.
    return day_of_month[mm];
}

//  is_leaf_year 함수 정의
int is_leaf_year(int yyyy)
{
    //  yyyy 값이 400의 배수인 경우 윤년
    if(yyyy % 400 == 0)
        //  1 반환
        return 1;
    
    //  yyyy 값이 4의 배수이면서 100의 배수가 아닌 경우 윤년
    if((yyyy % 100 != 0) && (yyyy % 4 == 0))
        //  1 반환
        return 1;
    
    //  윤년이 아님. 0을 반환
    return 0;
}
