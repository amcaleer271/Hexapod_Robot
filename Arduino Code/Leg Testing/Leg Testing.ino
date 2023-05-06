#include <Servo.h>

Servo hipYaw;   //horizontal motion in hip
Servo hipPitch; //vertical motion in hip

void setup() {
  hipYaw.attach(3);  
  hipPitch.attach(5):  

//init both servos to a middle pos

  hipYaw.write(90);
  hipPitch.write(90);

}

void loop() {
  
}