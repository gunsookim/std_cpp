#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial HM10(0, 1);  // (rx, tx), hm10 블루투스 연결
Servo mg[4]; // 서보모터 4개 배열로 선언 mg995  
Servo servo; // 기본 서보 모터 

const int servoPin = 11;  // 컨베이어 담당 모터의 핀 번호
const int servo1 = 2;     // 재료별 모터의 핀 번호
const int servo2 = 3;
const int servo3 = 4;
const int servo4 = 5;     // 용기 세팅 서보 모터 핀번호
const int speedDC = 6;    // dc모터 드라이버 속도 제어용 핀 번호 - 워터펌프 제어
const int relayPin = 7;   // 릴레이 모듈 핀 번호
const int IN1 = 12;       // 모터 드라이버 연결 핀 번호 1
const int IN2 = 13;       // 모터 드라이버 연결 핀 번호 2

int pos = 0;  // 컨베이어 벨트 초기 위치 값 
int recipe[10][10][2] = {
    {{0,1}, {1,1}, {2,1}, {3,1}, {4,1}}, // 메뉴1
    {{2,1}, {1,1}, {3,1}, {4,1}, {5,1}}, // 메뉴2
    {{2,1}, {1,1}, {3,1}, {4,1}, {5,1}} // 메뉴3
    };
// {메뉴, 순서별 재료 위치, 재료 용량}을 의미, 위치의 마지막 요소는 인덕션(0)을 의미 
// 1번 요소: 0-초기 위치, 1-면, 2-스프, 3-물, 4-인덕션 [][재료][]

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  HM10.begin(9600);
  mg[0].attach(servoPin);
  mg[1].attach(servo1);
  mg[2].attach(servo2);
  mg[3].attach(servo3);
  servo.attach(servo4);
  pinMode(relayPin, OUTPUT);
  pinMode(IN1, OUTPUT); // 모터 드라이버 제어용 핀 '출력모드'
  pinMode(IN2, OUTPUT); // 모터 드라이버 제어용 핀 '출력모드'
}

void conveyor(int b_loc, int a_loc){
  // 다음 재료 위치까지 컨베이어 작동
  if(b_loc >= a_loc){
    mg[0].write(0); //시계 방향으로 3초간 회전 
    delay(3000*(b_loc - a_loc));
    mg[0].write(90); //정지
    
  }
  else{
    mg[0].write(180); //반시계 방향으로 3초간 회전 
    delay(3000*(a_loc - b_loc));
    mg[0].write(90); //정지력
  }
}

void ingredient(int m){
  servo.write(180);
  delay(30);
  servo.write(0);
  delay(30);
  conveyor(0, 1);  // 용기를 첫 재료 아래로 이동
  // 재료 순서대로 투하
  for(int i = 1; i < 10; i++){
    pos = recipe[m][i][0];
    if(recipe[m][i][0] == 0){         // 재료 투하가 끝나면 pos 초기화
      conveyor(recipe[m][i][0], 0);
    }
    if(recipe[m][i][1] != 0){
      mg[i].write(180);                 // 해당 재료 담당 모터 작동
      delay(3000*recipe[m][i+1][1]);    // 투하량 조절
      mg[i].write(90);                  // 해당 재료 담당 모터 정지
      conveyor(pos, recipe[m][i+1][0]); // 다음 위치로 이동
    }
  }
  // 워터 펌프 동작
  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW);
  delay(2000);
  // 워터 펌프 정지
  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, HIGH);
  // 인덕션 동작 및 조리완료 알림 코드 필요 ***
  
}

void loop() {
  int menu = 0;
  // put your main code here, to run repeatedly:
  // 블루투스 통신, 
  if(Serial.available()) {   //시리얼포트에 데이터가 존재할 경우
    menu = HM10.read();      // 메뉴 입력
    ingredient(menu);
  }
}
