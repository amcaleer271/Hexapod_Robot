#include <Servo.h>

Servo joint[25];  //create an array of 18 servo objects

void setup() {
  joint[24].write(120);
  joint[23].write(0);
  joint[22].write(0);

  joint[21].write(50);
  joint[20].write(10);
  joint[19].write(20);

  joint[18].write(100);
  joint[17].write(5);
  joint[16].write(20);

  joint[7].write(90);
  joint[8].write(170);
  joint[9].write(155);

  joint[4].write(90);
  joint[5].write(170);
  joint[6].write(158);

  joint[1].write(100);
  joint[2].write(177);
  joint[3].write(185);


  Serial.begin(9600);

//attach all servo objects to respective ports
  for(int i = 1; i<=25; i++){
    joint[i].attach(21 + i);
  }
  Serial.println("Servos Attached");
  delay(1000);
  
}

void loop() {
  move11(0);
  move12(0);
  move13(0);

  move21(0);
  move22(0);
  move23(0);

  move31(0);
  move32(0);
  move33(0);

  move41(0);
  move42(0);
  move43(0);

  move51(0);
  move52(0);
  move53(0);

  move61(0);
  move62(0);
  move63(0);
}

//move all serovs to a specified angle
void moveAll(int pos){
   for(int j = 0; j<=25; j++){
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
  for(int i = 0; i <= 100; i++){
    joint[testingJoint].write(i);
    delay(20);
  }
  for(int i = 100; i >= 50; i--){
    joint[testingJoint].write(i);
    delay(20);
  }
}

void move11(int pos){   //range 0-100
  joint[24].write(120 + pos);
}

void move12(int pos){  
  joint[23].write(pos);
}

void move13(int pos){
  joint[22].write(pos);
}

void move21(int pos){
  joint[21].write(50 + pos);
}

void move22(int pos){
  joint[20].write(10 + pos);
}

void move23(int pos){
  joint[19].write(20 + pos);
}

void move31(int pos){
  joint[18].write(100 + pos);
}

void move32(int pos){
  joint[17].write(5 + pos);
}

void move33(int pos){
  joint[16].write(20 + pos);
}

void move41(int pos){
  joint[7].write(90 + pos);
}

void move42(int pos){
  joint[8].write(170 + pos);
}

void move43(int pos){
  joint[9].write(155 + pos);
}

void move51(int pos){
  joint[4].write(90 + pos);
}

void move52(int pos){
  joint[5].write(170 + pos);
}

void move53(int pos){
  joint[6].write(158 + pos);
}

void move61(int pos){
  joint[1].write(100 + pos);
}

void move62(int pos){
  joint[2].write(177 + pos);
}

void move63(int pos){
  joint[3].write(185 + pos);
}