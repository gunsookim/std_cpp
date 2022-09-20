#include <Servo.h>

/*
회로 연결
8pin - bottom
9pin - arm1
10pin - arm2
11pin - gripper
*/

Servo bottom;
Servo arm1;
Servo arm2;
Servo grip;

void setup() {
  bottom.attach(8);
  arm1.attach(9);
  arm2.attach(10);
  grip.attach(11);

  bottom.write(90);
  arm1.write(90);
  arm2.write(90);
  grip.write(90);
}

void loop() {
}
