// C++ code
//
#define NUMBER_OF_SHIFT_CHIPS   1

/* Width of data (how many ext lines).
*/
#define DATA_WIDTH   NUMBER_OF_SHIFT_CHIPS * 8

/* Width of pulse to trigger the shift register to read and latch.
*/
#define PULSE_WIDTH_USEC   5

/* Optional delay between shift register reads.
*/
#define POLL_DELAY_MSEC   1

/* You will need to change the "int" to "long" If the
 * NUMBER_OF_SHIFT_CHIPS is higher than 2.
*/
#define BYTES_VAL_T unsigned int
#define NUMBER_OF_SHIFT_CHIPS   1

/* Width of data (how many ext lines).
*/
#define DATA_WIDTH   NUMBER_OF_SHIFT_CHIPS * 8

/* Width of pulse to trigger the shift register to read and latch.
*/
#define PULSE_WIDTH_USEC   5

/* Optional delay between shift register reads.
*/
#define POLL_DELAY_MSEC   1

/* You will need to change the "int" to "long" If the
 * NUMBER_OF_SHIFT_CHIPS is higher than 2.
*/
#define BYTES_VAL_T unsigned int


#include <SoftwareSerial.h>
#include <Servo.h>
#include <Wire.h>                       // I2C 통신을 위한 헤더파일
#include <Adafruit_PWMServoDriver.h>    // 서보모터 다중제어를 위한 헤더파일

Adafruit_PWMServoDriver pwm=Adafruit_PWMServoDriver();

SoftwareSerial HM10(0, 1);  // (rx, tx), hm10 블루투스 연결
Servo soup[4]; // 서보모터 객체 4개 생성
Servo belt[2]; // 컨베이어 벨트 동작 서보 모터 객체 2개 생성
Servo servo; // 기본 서보 모터 객체 생성 - 용기 셋팅
Servo stuff; // 서보모터 객체 1개 생성

const int servoPin1 = 10;  // 컨베이어 담당 모터 1을 10번 핀에 연결: 라면용
const int servoPin2 = 11;  // 컨베이어 담당 모터 2을 11번 핀에 연결: 용기 이동용
const int servo1 = 2;     // 서보 모터 4개를 각각 2~5핀에 연결: 스프 종류 결정
const int servo2 = 3;
const int servo3 = 4;
const int servo4 = 5;
const int servo5 = 9;     // 서보 모터 5를 9핀에 연결: 건더기 담당
const int servoBowl = 6;     // 용기 세팅 서보 모터를 6번 핀에 연결
const int speedDC = 7;    // dc모터 드라이버 속도 제어용 핀 번호 7 - 워터펌프 제어
const int relayPin = 8;   // 릴레이 모듈 핀 번호 8
const int IN3 = 12;       // 모터 드라이버 연결 핀 번호 1
const int IN4 = 13;       // 모터 드라이버 연결 핀 번호 2
int ploadPin        = A0;  // Connects to Parallel load pin the 165
int clockEnablePin  = A1;  // Connects to Clock Enable pin the 165
int dataPin         = A2; // Connects to the Q7 pin the 165
int clockPin        = A3; // Connects to the Clock pin the 165

BYTES_VAL_T pinValues;
BYTES_VAL_T oldPinValues;


String key[4] = {"진라면", "신라면", "짜파게티", "너구리"}; int value[4] = {1,2,3,4};
int pos = 0;  // 컨베이어 벨트 초기 위치 값
int recipe[3][5][2] = { // recipe[메뉴 종류][재료 위치][재료 용량]
    {{0,0}, {1,1}, {2,1}, {3,1}, {4,1}}, // 메뉴1
    {{0,0}, {1,0}, {2,1}, {3,1}, {4,1}}, // 메뉴2
    {{0,0}, {1,1}, {3,1}, {4,1}, {5,1}}  // 메뉴3
    };
/* [재료 위치]- 첫번째 인덱스: 그릇 셋팅, 마지막 인덱스: 인덕션, 나머지: 재료
   [재료 용량]- g(그람)을 기준으로 설정
*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  HM10.begin(9600);
  belt[0].attach(servoPin1); // 컨베이어 벨트 동작을 담당
  belt[1].attach(servoPin2); // 면 투하
  soup[1].attach(servo1);
  soup[2].attach(servo2);
  soup[3].attach(servo3);
  soup[4].attach(servo4);
  servo.attach(servoBowl);
  // 모든 핀들을 출력 모드로 초기화
  pinMode(servoPin1, OUTPUT);
  pinMode(servoPin2, OUTPUT);
  pinMode(servo1, OUTPUT);
  pinMode(servo2, OUTPUT);
  pinMode(servo3, OUTPUT);
  pinMode(servo4, OUTPUT);
  pinMode(servo5, OUTPUT);
  pinMode(servoBowl, OUTPUT);
  pinMode(relayPin, OUTPUT); // 릴레이 모듈 제어 핀 출력모드
  pinMode(IN3, OUTPUT); // 모터 드라이버 제어용 핀 '출력모드'
  pinMode(IN4, OUTPUT); // 모터 드라이버 제어용 핀 '출력모드'
}

// 딕셔너리 동작 구현 함수: 스프 이름 -> 정수 대응
int dictionary(String _key){ int i; for(i=0;i<5;i++){if(_key==key[i]){ return value[i]; }}}


// 그릇 투하 함수
void set_bowl(){  
  servo.write(180);
  delay(30);
  servo.write(0);
  delay(30);
  // conveyor(0, 1);  // 용기를 첫번째 재료 아래로 이동
}

// 라면 투하 함수
void set_noodle(){
  // 면 투하
  belt[1].write(180);
  delay(3000);
  // 원위치
  belt[2].write(0);
  delay(3000);
}

// 컨베이어 벨트 동작 함수: 다음 재료 위치까지 그릇 이동 
void conveyor(int b_loc, int a_loc){
  if(b_loc >= a_loc){
    belt[0].write(0); // 시계 방향으로 3초간 회전 
    delay(3500*(b_loc - a_loc));
    belt[0].write(90); // 정지
    
  }
  else{
    belt[0].write(180); // 반시계 방향으로 3초간 회전 
    delay(3000*(a_loc - b_loc));
    belt[0].write(90); // 정지
  }
}

// 물 공급 함수 - 입력값 w에 따라 공급량 조절 가능
void set_water(int w){ 
  // 워터 펌프 동작
  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, LOW);
  delay(2000*w);
  // 워터 펌프 정지
  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, HIGH);
}

// 라면 스프 투하
void soup_type(int type){
  soup[type+1].write(90);
}

// 재료 투하 함수
void ingredient(int m){
  int water = 1;
  
  // 용기 세팅
  set_bowl();
  
  // 재료 순서대로 투하
  for(int i = 1; i < 4; i++){
    pos = recipe[m][i][0];
    if(recipe[m][i][0] == 0){         // 재료 투하가 끝나면 벨트 원위치 --> 필요한가?
      conveyor(recipe[m][i][0], 0);
     }
    soup[i].write(180);               // 해당 재료 담당 모터 작동
    delay(1000*recipe[m][i+1][1]);    // 투하량 조절
    soup[i].write(90);                // 해당 재료 담당 모터 정지
    conveyor(pos, recipe[m][i+1][0]); // 다음 위치로 이동
  }
  
  // 물 공급 
  set_water(water);
  
  // 인덕션 동작 및 조리완료 알림 코드 필요 ***  
}

// 메인 함수
void loop() {
  int menu = 0;
  // put your main code here, to run repeatedly:
  /*
  while (HM10.available()){ 
    byte data = HM10.read();
    Serial.write(data);
  }   
  while (Serial.available()){
    byte data = Serial.read();
    HM10.write(data); 
  }*/
  // 블루투스 통신 동작 확인
  if(HM10.available()) {
    byte input_txt = HM10.read();      // 메뉴 입력
    Serial.write(input_txt);
    menu = (int) input_txt;
    ingredient(menu);
  }
  // 재료 투하 동작 확인
  ingredient(menu);
  // 완료 알림
  Serial.println("조리 완료"); 
  exit(0);
}
