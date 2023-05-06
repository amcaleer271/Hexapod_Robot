#include <Servo.h>

Servo servo1;

void setup() {
  servo1.attach(3);  // attaches the servo on pin 3 to the servo object
}

void loop() {
  for(int i = 0; i < 180; i++){
    servo1.write(i);
    delay(5);
  }
  for(int j = 180; j > 0; j--){
    servo1.write(j);
    delay(5);
  }
}