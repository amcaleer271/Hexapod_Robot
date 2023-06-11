#include <Servo.h>

Servo joint[18];

void setup() {

  Serial.begin(9600);

  for(int i = 1; i<=18; i++){
    joint[i].write(50);
    joint[i].attach(22+i);
    

  }
}

void loop() {
  delay(1500);
  testJoint(1,0,100);
  delay(1500);
  testJoint(2,0,160);
  delay(1500);
  testJoint(3,0,100);
  // delay(1500);
  // testJoint(4,0,100);
  // delay(1500);
  // testJoint(5,0,160);
  // delay(1500);
  // testJoint(6,0,160);
  // delay(1500);
  // testJoint(7,25,100);
  // delay(1500);
  // testJoint(8,0,160);
  // delay(1500);
  // testJoint(9,0,160);

}
// void moveAll(int pos){
//   for(int j = 1; j<=18; j++){
//     joint[j].write(pos);
//   }
// }

void testJoint(int jointNum, int left, int right){
  for(int i = left; i <=right; i++){
    joint[jointNum].write(i);
    delay(25);
  }
  for(int i = right; i >= left; i--){
    joint[jointNum].write(i);
    delay(25);
  }
}