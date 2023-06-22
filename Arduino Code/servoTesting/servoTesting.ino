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

  joint[1].write(85);
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
  
}

void walkf(int period, int steps){
  for(int i = 0; i <= steps; i++){
    int group1 = i;
    int group2 = i + steps/2;
    if(group2 > steps){
      group2 = group2 % steps;
    }
    move11(group1);
    move21(group2);
    move31(group1);

    move61(-1 * group2);
    move51(-1 * group1);
    move41(-1 * group2);
    delay(1000 * period / steps);
  }

}
void leg1f(int period, int steps, int shift){    
  //period = time [s] for 1 loop, steps = num steps in loop, shift = phase shift
  //default period = 1 sec, steps = 60, shift = 0
  for(int i = 0; i <= steps; i++){
    int movement = i + shift;
    if(movement > steps){
      movement = movement % steps;
    }
    move11(movement);
    delay(1000 * period / steps);
  }
}

void leg6f(int period, int steps, int shift){
  //period = time [s] for 1 loop, steps = num steps in loop, shift = phase shift
  //default period = 1 sec, steps = 60, shift = 0
  for(int i = 0; i <= steps; i++){
    int movement = i + shift;
    if(movement > steps){
      movement = movement % steps;
    }
    move61(-1 * movement);
    delay(1000 * period / steps);
  }
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
  joint[1].write(85 + pos);
}

void move62(int pos){
  joint[2].write(177 + pos);
}

void move63(int pos){
  joint[3].write(185 + pos);
}