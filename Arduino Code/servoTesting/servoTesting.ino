#include <Servo.h>

Servo joint[25];  //create an array of 18 servo objects


void setup() {

  Serial.begin(9600);

//attach all servo objects to respective ports
  for(int i = 1; i<=25; i++){
    joint[i].attach(21 + i);
  }
  Serial.println("Servos Attached");
  delay(1000);
  standTest();
}

void loop() {
  

}

//move all serovs to a specified angle
void moveAll(int pos){
   for(int j = 1; j<=18; j++){
     joint[j].write(pos);
   }
}

//prompted to enter a servo to test, then rotates 50 degrees back/forth
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

void standTest(){

  Serial.println("Standing...");

  for(int i = 1; i <= 100; i++){
    joint[23].write(49 + i);
    joint[20].write(49 + i);
    joint[17].write(49 + i);

    joint[2].write(101 - i);
    joint[5].write(101 - i);
    joint[8].write(101 - i);

    delay(30);
  }
}

