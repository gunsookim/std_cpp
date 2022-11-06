// C++ code
//
#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial HM10(0, 1);  // (rx, tx), hm10 블루투스 연결
Servo mg[4]; // 서보모터 4개 배열로 선언 mg995  
Servo servo; // 기본 서보 모터 

const int servoPin = 11;  // 컨베이어 담당 모터의 핀 번호
const int servo1 = 2;     // 각각의 서보 모터를 제어할 핀 번호
const int servo2 = 3;
const int servo3 = 4;
const int servo4 = 5;     // 용기 세팅 서보 모터 핀번호
const int speedDC = 6;    // dc모터 드라이버 속도 제어용 핀 번호 - 워터펌프 제어
const int relayPin = 7;   // 릴레이 모듈 핀 번호
const int IN3 = 12;       // 모터 드라이버 연결 핀 번호 1
const int IN4 = 13;       // 모터 드라이버 연결 핀 번호 2

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
  mg[0].attach(servoPin); // mg[0]가 컨베이어 벨트 동작을 담당
  mg[1].attach(servo1);
  mg[2].attach(servo2);
  mg[3].attach(servo3);
  servo.attach(servo4);
  pinMode(relayPin, OUTPUT);
  pinMode(IN3, OUTPUT); // 모터 드라이버 제어용 핀 '출력모드'
  pinMode(IN4, OUTPUT); // 모터 드라이버 제어용 핀 '출력모드'
}

// 그릇 투하 함수
void set_bowl(){  
  servo.write(180);
  delay(30);
  servo.write(0);
  delay(30);
  conveyor(0, 1);  // 용기를 첫번째 재료 아래로 이동
}


// 컨베이어 벨트 동작 함수: 다음 재료 위치까지 그릇 이동 
void conveyor(int b_loc, int a_loc){
  if(b_loc >= a_loc){
    mg[0].write(0); // 시계 방향으로 3초간 회전 
    delay(3500*(b_loc - a_loc));
    mg[0].write(90); // 정지
    
  }
  else{
    mg[0].write(180); // 반시계 방향으로 3초간 회전 
    delay(3000*(a_loc - b_loc));
    mg[0].write(90); // 정지력
  }
}

// 재료 투하 함수
void ingredient(int m){
  // 용기 세팅 코드
  set_bowl();
  
  // 재료 순서대로 투하
  for(int i = 1; i < 4; i++){
    pos = recipe[m][i][0];
    if(recipe[m][i][0] == 0){         // 재료 투하가 끝나면 벨트 원위치 --> 필요한가?
      conveyor(recipe[m][i][0], 0);
     }
    mg[i].write(180);                 // 해당 재료 담당 모터 작동
    delay(1000*recipe[m][i+1][1]);    // 투하량 조절
    mg[i].write(90);                  // 해당 재료 담당 모터 정지
    conveyor(pos, recipe[m][i+1][0]); // 다음 위치로 이동
  }
  // 워터 펌프 동작
  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, LOW);
  delay(2000);
  // 워터 펌프 정지
  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, HIGH);
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