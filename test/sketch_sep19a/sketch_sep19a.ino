#include <SoftwareSerial.h>
#include <Servo.h>


SoftwareSerial BTSerial(4, 5);  // hm10의 tx, rx선과 연결
Servo mg995;

const int servoPin = 10;
const int servoIng[] = 1, 2, 3;
// const int servoIng[] = 
int pos = 0;
int ing_loc[] = {1, 2, 3, 4, 5, 6, 7, 10} //재료 위치 번호 저장
// 마지막 요소는 항상 10(인덕션을 의미)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BTSerial.begin(9600);
  mg995.attach(servoPin);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void conveyor(b_loc, a_loc){
  if(b_loc >= a_loc){
    servoPin.write(0); //시계 방향으로 3초간 회전 
    delay(3000*(b_loc - a_loc));
    servoPin.write(0); //정지
    
  }
  else{
    servoPin.write(180); //반시계 방향으로 3초간 회전 
    delay(3000*(a_loc - b_loc));
    servoPin.write(0); //정지
  }
}

void ingredient(ing){
  // 재료 순서대로 투하
  for(int i = 0; i < (sizeof(ing) - 1); i++){
    if(i != 0) pos = ing_loc[i];
    servoIng[i].write(180);
    delay(1000);
    conveyor(pos, ing_loc[i+1])
  }
}
