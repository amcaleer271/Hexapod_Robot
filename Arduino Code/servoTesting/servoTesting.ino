#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;

void setup() {
  servo1.attach(3);  
  servo2.attach(5);
  servo3.attach(6);

  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
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