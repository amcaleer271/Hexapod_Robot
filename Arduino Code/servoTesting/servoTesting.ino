#include <Servo.h>

Servo joint[25];  //create an array of 18 servo objects


void setup() {

  Serial.begin(9600);

//attach all servo objects to respective ports
  for(int i = 1; i<=25; i++){
    joint[i].attach(21 + i);
  }
  Serial.println("Servos Attached");
}

void loop() {


  

}

//move all serovs to a specified angle
void moveAll(int pos){
   for(int j = 1; j<=18; j++){
     joint[j].write(pos);
   }
}

void individualTest(){
  Serial.println("Enter joint to test: ");
  while(Serial.available() == 0){
    //empty loop
  }
  int testingJoint = Serial.parseInt();
  for(int i = 50; i <= 100; i++){
    joint[testingJoint].write(i);
    delay(20);
  }
  for(int i = 100; i >= 50; i--){
    joint[testingJoint].write(i);
    delay(20);
  }
}