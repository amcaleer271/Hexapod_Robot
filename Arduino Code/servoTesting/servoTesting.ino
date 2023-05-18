#include <Servo.h>

Servo joint[18];

void setup() {
  for(int i = 1; i<=18; i++){
    joint[i].attach(22+i);
  }
  moveAll(90);
}

void loop() {
//   for(int i = 0; i < 180; i++){
//     servo1.write(i);
//     delay(5);
//   }
//   for(int j = 180; j > 0; j--){
//     servo1.write(j);
//     delay(5);
//   }
}

void moveAll(int pos){
  for(int j = 1; j<=18; j++){
    joint[j].write(pos);
  }
}