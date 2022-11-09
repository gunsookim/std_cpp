// C++ code
//

#include <SoftwareSerial.h>
#include <Servo.h>
#include <Wire.h>                       // I2C 통신을 위한 헤더파일
#include <Adafruit_PWMServoDriver.h>    // 서보모터 다중제어를 위한 헤더파일

Adafruit_PWMServoDriver pwm=Adafruit_PWMServoDriver();

SoftwareSerial HM10(6, 7);  // (rx, tx), hm10 블루투스 연결
Servo soup[4]; // 서보모터 객체 4개 생성
Servo belt[2]; // 컨베이어 벨트 동작 서보 모터 객체 2개 생성
Servo servo; // 기본 서보 모터 객체 생성 - 용기 셋팅
Servo stuff; // 서보모터 객체 1개 생성

const int speedDC = 7;    // dc모터 드라이버 속도 제어용 핀 번호 7 - 워터펌프 제어
const int relayPin = 8;   // 릴레이 모듈 핀 번호 8
const int IN3 = 12;       // 모터 드라이버 연결 핀 번호 1
// PCA9685 모듈 연결 핀 번호 = A4, A5

/* 74hc165 연결 핀 번호
int ploadPin        = A0;  // Connects to Parallel load pin the 165
int clockEnablePin  = A1;  // Connects to Clock Enable pin the 165
int dataPin         = A2; // Connects to the Q7 pin the 165
int clockPin        = A3; // Connects to the Clock pin the 165
*/

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
  // pca9685 setup code
  pwm.begin();
  pwm.setPWMFreq(51);
  // 모든 핀들을 출력 모드로 초기화
  pinMode(relayPin, OUTPUT); // 릴레이 모듈 제어 핀 출력모드
  pinMode(IN3, OUTPUT); // 모터 드라이버 제어용 핀 '출력모드'
}

// 딕셔너리 동작 구현 함수: 스프 이름 -> 정수 대응
int dictionary(String _key){ int i; for(i=0;i<5;i++){if(_key==key[i]){ return value[i]; }}}

void set_servo(){
  int a = Serial.parseInt();
  int servo_ing[4]={1,2,3,4};
  int servo_mini[1]={5};
  int servo_mg[2]={6,7};
  //  받은 값의 범위 0~180을 펄스길이150~600으로 매핑해주고, ra의 최소,최대를 150,600을 넘지 않게 해준다.
  int ra = constrain(map(a, 0, 180, 150, 600), 150, 600); 
  pwm.setPWM(0,0,ra); //  pca9685모듈의 0번 포트에 연결된 서보를 ra만큼 회전   
  pwm.setPWM(1,0,ra); //  pca9685의 1번에 연결된 서보를 ry만큼 회전
}

// 그릇 투하 함수
void set_bowl(){
  
}

// 라면 투하 함수
void set_noodle(){
  
}

// 컨베이어 벨트 동작 함수: 다음 재료 위치까지 그릇 이동 
void conveyor(int b_loc, int a_loc){
  
}

// 물 공급 함수 - 입력값 w에 따라 공급량 조절 가능
void set_water(int w){ 
  // 워터 펌프 동작
  digitalWrite(IN3, HIGH); 
  delay(2000*w);
  // 워터 펌프 정지
  digitalWrite(IN3, HIGH); 
}

//  재료 투하 함수
void set_ingredent(){
  
}

// 메인 함수
void loop() {  
  String menu = "라면";
  // put your main code here, to run repeatedly:
  int a = 30;
  int ra = constrain(map(a, 0, 180, 150, 600), 150, 600); 
  pwm.setPWM(0,0,ra);
  delay(300);
  pwm.setPWM(0,0,0);
  /*
  pwm.setPWM(1,0,ra);
  delay(300);
  pwm.setPWM(1,0,0);
  pwm.setPWM(2,0,ra);
  delay(300);
  pwm.setPWM(2,0,0);
  pwm.setPWM(3,0,ra);
  delay(300);
  pwm.setPWM(3,0,0);
  pwm.setPWM(4,0,ra);
  delay(300);
  pwm.setPWM(4,0,0);
  pwm.setPWM(5,0,ra);
  delay(300);
  pwm.setPWM(5,0,0);
  */
  
  // 블루투스 통신 동작 확인
  if(HM10.available()) {
    byte input_txt = HM10.read();      // 메뉴 입력
    Serial.write(input_txt);
    menu = (int) input_txt;
  }
  
// 완료 알림
  Serial.println("조리 완료\n"); 
  exit(0);
}
