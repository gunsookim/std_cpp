#include <SoftwareSerial.h>
#include <Servo.h>


SoftwareSerial BTSerial(4, 5);  // hm10의 tx, rx선과 연결
Servo mg995;

const int servoPin = 10;
// const int servoIng[] = 
int pos = 0;
int ing_loc[] = {1, 2, 3, 4, 5, 6, 7} //재료 위치 번호 저장 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600)
  BTSerial.begin(9600)
  mg995.attach(servoPin);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void conveyor(b_loc, a_loc){
  if(b_loc >= a_loc){
    servoPin.write(0) //시계 방향으로 3초간 회전 
    delay(3000*(b_loc - a_loc))
    servoPin.write(0) //정지
    
  }
  else{
    servoPin.write(180) //반시계 방향으로 3초간 회전 
    delay(3000*(a_loc - b_loc))
    servoPin.write(0) //정지
  }
}

void ingredient(ing){
  
  int ing_loc[] = {1, 2, 3, 4, 5, 6, 7} //재료 위치 저장 
}
