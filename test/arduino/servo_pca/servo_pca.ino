#include <SoftwareSerial.h>
#include <Servo.h>
#include <Wire.h>                       // I2C 통신을 위한 헤더파일
#include <Adafruit_PWMServoDriver.h>    // 서보모터 다중제어를 위한 헤더파일

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

SoftwareSerial HM10(6, 7);  // (rx, tx), hm10 블루투스 연결

const int DirPin1 = 12;    // 모터드라이버 제어신호 핀 번호1
const int DirPin2 = 13;    // 모터드라이버 제어신호 핀 번호2
const int relayPin = 3;   // 릴레이 모듈 핀 번호 8
// PCA9685 모듈 연결 핀 번호 = A4, A5

// pca 서보모터 연결 핀 번호
const int servo_mg[4] = {0, 1, 2, 3}; //  컨베이어2, 면1, 인덕션1 -
const int servo_soup[4] = {4, 5, 6, 7}; //  스프
const int servo_mini[2] = {8, 9};     //  건더기2
const int servo_bowl[2] = {10, 11};   //  용기

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  HM10.begin(9600);
  // 모터 드라이버 setup
  pinMode(DirPin1, OUTPUT);   // 모터 드라이버 제어 1번핀 출력모드 설정
  pinMode(DirPin2, OUTPUT);   // 모터 드라이버 제어 2번핀 출력모드 설정
  // pca9685 setup code
  pwm.begin();
  pwm.setPWMFreq(52);
  // 모든 핀들을 출력 모드로 초기화
  pinMode(relayPin, OUTPUT);  // 릴레이 모듈 제어 핀 출력모드
}

// 물 공급 함수 - 입력값 w에 따라 공급량 조절 가능
void set_water(int w) {
  // 워터 펌프 동작
  digitalWrite(DirPin1, HIGH);
  digitalWrite(DirPin2, LOW);
  delay(2000 * w);
  // 워터 펌프 정지
  digitalWrite(DirPin1, HIGH);
  digitalWrite(DirPin2, HIGH);
}

// 메인 함수
void loop() {
  // put your main code here, to run repeatedly:
  /*   servo 제어 코드: pwm.setPWM({pca포트번호}, {on == 0}, {각도(0~180을 150~600으로 변환)})
       서보모터 포트 번호: 컨베이어-{0,1} / 면-{2} / 용기-{3} / 스프-{4,5,6,7} / 건더기-{8,9}
       mg995는 0~180로 mapping, mini 서보는 150~600 으로 mapping
  */
  if (Serial.available()) {
    
      String order = Serial.readStringUntil('\n');
      int comma1 = order.indexOf(',');
      int comma2 = order.indexOf(',', comma1+1);
      int len = order.length();
      int num_user = order.substring(0,comma1).toInt();       // 첫번째 수 = 주문번호
      int menu = order.substring(comma1+1,comma2).toInt();    // 두번째 수 = 스프 종류
      int option1 = order.substring(comma2+1,len).toInt();    // 세번째 수 = 옵션
      Serial.println(order);
      Serial.println(num_user);
      Serial.println(menu);
      Serial.println(option1);

      
      pwm.setPWM(servo_mg[0],0,180);
      pwm.setPWM(servo_mg[1],0,400);
      delay(1000);
      pwm.setPWM(servo_mg[0],0,0);
      pwm.setPWM(servo_mg[1],0,0);

      //  용기 투하
      pwm.setPWM(servo_bowl[0],0,300);
      pwm.setPWM(servo_bowl[1],0,300);
      delay(300);
      pwm.setPWM(servo_bowl[0],0,150);
      pwm.setPWM(servo_bowl[1],0,150);

      //  면 투하
      pwm.setPWM(servo_mg[2],0,180);
      delay(2000);
      pwm.setPWM(servo_mg[2],0,360);
      delay(2000);
      pwm.setPWM(servo_mg[2],0,0);
    
      //  컨베이어 작동 및 재료 투하
      pwm.setPWM(servo_mg[0], 0, 180);
      pwm.setPWM(servo_mg[1], 0, 400);
      delay(3000);
      pwm.setPWM(servo_mg[0], 0, 0);
      pwm.setPWM(servo_mg[1], 0, 0);
      delay(4000);

    
      pwm.setPWM(servo_mg[0],0,180);
      pwm.setPWM(servo_mg[1],0,400);
      delay(500);
      pwm.setPWM(servo_mg[0],0,0);
      pwm.setPWM(servo_mg[1],0,0);

      pwm.setPWM(servo_soup[menu],0,300);   // 해당 스프 투하
      delay(100*option1);                   // 옵션1 - 양 조절
      pwm.setPWM(servo_soup[menu],0,150);

      pwm.setPWM(servo_mg[0],0,180);
      pwm.setPWM(servo_mg[1],0,400);
      delay(2000);
      pwm.setPWM(servo_mg[0],0,0);
      pwm.setPWM(servo_mg[1],0,0);

      pwm.setPWM(servo_mini[0],0,300);   // 건더기 1 투하
      delay(100);
      pwm.setPWM(servo_mini[0],0,150);
      pwm.setPWM(servo_mini[1],0,300);   // 건더기 2 투하
      delay(100);
      pwm.setPWM(servo_mini[1],0,150);

      pwm.setPWM(servo_mg[0],0,180);
      //pwm.setPWM(servo_mg[1],0,400);
      delay(2000);
      pwm.setPWM(servo_mg[0],0,0);
      //pwm.setPWM(servo_mg[1],0,0);
      //  인덕션 동작
      pwm.setPWM(servo_mg[3],0,180);
      delay(1000);
      pwm.setPWM(servo_mg[3],0,0);
    
    Serial.print("주문 번호: ");
    Serial.println(num_user);
    Serial.println("조리완료");
  }
}
