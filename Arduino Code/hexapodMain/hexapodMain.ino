#include <Servo.h>

Servo joint[25];  //create an array of 18 servo objects
int voltagePin = 3;
int led = 7;
int isTurning;
int lastMsg = 0;

int walkStep = 34;
int controllerVal;

void setup() {
  joint[24].write(160);
  joint[23].write(150);
  joint[22].write(60);

  joint[21].write(90);
  joint[20].write(160);
  joint[19].write(80);

  joint[18].write(160);
  joint[17].write(155);
  joint[16].write(80);

  joint[7].write(30);
  joint[8].write(20);
  joint[11].write(95);

  joint[4].write(50);
  joint[5].write(20);
  joint[6].write(98);

  joint[1].write(45);
  joint[2].write(27);
  joint[3].write(105);

  pinMode(led, OUTPUT);

  Serial.begin(9600);

//attach all servo objects to respective ports
  for(int i = 1; i<=25; i++){
    joint[i].attach(21 + i);
  }
  
  digitalWrite(led, HIGH);
}

void loop() {
  
  checkBattery();

  //get value from controller, if forward increase walk step, if reverse decrease walk step, else do nothing
  controllerVal = radioDecode();
  
  if(controllerVal == 8){
    isTurning = 0;
    if(walkStep >= 74){
      walkStep = 1;
    }
    else{
      walkStep += 1;
    }
  }
  else if(controllerVal == 2){
    isTurning = 0;
    if(walkStep <= 0){
      walkStep = 73;
    }
    else{
      walkStep -= 1;
    }
  }
  else if(controllerVal == 4){
    isTurning = 1;
    if(walkStep <= 0){
      walkStep = 73;
    }
    else{
      walkStep -= 1;
    }
  }
  else if(controllerVal == 6){
    isTurning = 1;
    if(walkStep >= 74){
      walkStep = 1;
    }
    else{
      walkStep += 1;
    }
  }
  Serial.println(controllerVal);
  controllerWalk(walkStep, 1, 38, 0, isTurning, 1);
  delay(15);
  
}

void controllerWalk(int currentStep, int period, int steps, int direction, int turning, int enable){
  float group1;
  float group2;
  float group1Hip;
  float group2Hip;
  float group1Knee;
  float group2Knee;
  float group1Foot;
  float group2Foot;
  int i = currentStep;
  int hStep = steps/2;

  //calculate hip angles
  group1 = hStep + hStep * cos(2 * 3.14159 * i / (2*steps));
  group2 = hStep + hStep * cos((2 * 3.14159 * i / (2*steps)) + 3.14159);

  group1Hip = group1;
  group2Hip = group2;

  //calculate knee angles
  if((i % (2 * steps)) < steps){
    group1Knee = 180;
    group2Knee = 180 - 2 *(hStep + hStep * cos((2 * 3.14159 * i / steps) + 3.14159));
  }
  else{
    group1Knee = 180 - 2 * (hStep + hStep * cos((2 * 3.14159 * i / steps) + 3.14159));
    group2Knee = 180;
  }
  
  //calculate foot angles
  if(group1Knee == 180){
    group1Foot = 0;
    group2Foot = 180 - group2Knee;
  }
  else{
    group1Foot = 180 - group1Knee;
    group2Foot = 0;
  }

  if(enable == 1){
    if(turning == 1){
      //upper limbs
      move11(1.1*group1Hip + 30);
      move21(1.1*group2Hip + 30);
      move31(1.1*group1Hip + 55);

      move61(30 - 1.1*group1Hip);
      move51(30 - 1.1*group2Hip);
      move41(30 - 1.1*group1Hip);

      //middle limbs
      move12(group1Knee);
      move22(group2Knee);
      move32(group1Knee);

      move62(-1 * group2Knee);
      move52(-1 * group1Knee);
      move42(-1 * group2Knee);

      //end limbs        
      move13(-1 * group1Foot + 110);
      move23(-1 * group2Foot + 110);
      move33(-1 * group1Foot + 110);

      move63(group2Foot - 110);
      move53(group1Foot - 110);
      move43(group2Foot - 110);
    }
    else{
      //upper limbs
      move11(1.1*group1Hip + 30);
      move21(1.1*group2Hip + 30);
      move31(1.1*group1Hip + 55);

      move61(-1 * 0.7*group2Hip - 30);
      move51(-1 * 0.7*group1Hip - 30);
      move41(-1 * 0.7*group2Hip - 55);

      //middle limbs
      move12(group1Knee);
      move22(group2Knee);
      move32(group1Knee);

      move62(-1 * group2Knee);
      move52(-1 * group1Knee);
      move42(-1 * group2Knee);

      //end limbs        
      move13(-1 * group1Foot + 110);
      move23(-1 * group2Foot + 110);
      move33(-1 * group1Foot + 110);

      move63(group2Foot - 110);
      move53(group1Foot - 110);
      move43(group2Foot - 110);
    }
  }

  //debug info
  // Serial.print("i: ");
  // Serial.print(i);
  // Serial.print(" , group1: ");
  // Serial.print(group1);
  // Serial.print(" , group2: ");
  // Serial.print(group2);
  // Serial.print(" , group1Knee: ");
  // Serial.print(group1Knee);
  // Serial.print(" , group2Knee: ");
  // Serial.print(group2Knee);
  // Serial.print(" , group1Foot: ");
  // Serial.print(group1Foot);
  // Serial.print(" , group2Foot: ");
  // Serial.println(group2Foot);
}



//convert the binary signals from the recieving arduino into an integer 1-9
int radioDecode(){
  int outputVal;
  if(digitalRead(3) == LOW && digitalRead(5) == LOW){
    if(digitalRead(6) == LOW && digitalRead(4) == LOW){
      outputVal = 5;
    }
    else if(digitalRead(6) == HIGH && digitalRead(4) == LOW){
      outputVal = 8;
    }
    else{
      outputVal = 2;
    }
  }
  else if(digitalRead(3) == HIGH && digitalRead(5) == LOW){
    if(digitalRead(6) == LOW && digitalRead(4) == LOW){
      outputVal = 4;
    }
    else if(digitalRead(6) == HIGH && digitalRead(4) == LOW){
      outputVal = 7;
    }
    else{
      outputVal = 1;
    }
  }
  else{
    if(digitalRead(6) == LOW && digitalRead(4) == LOW){
      outputVal = 6;
    }
    else if(digitalRead(6) == HIGH && digitalRead(4) == LOW){
      outputVal = 9;
    }
    else{
      outputVal = 3;
    }
  }
  return(outputVal);
}

//checks battery voltage is above 12.4v
void checkBattery(){
  if(analogRead(voltagePin) < 840){
    for(int i = 0; i<=3; i++){
      delay(1000);
      digitalWrite(led, LOW);
      delay(1000);
      digitalWrite(led, HIGH);
    }
  }
}

//params - period [s], steps [steps], offset [rads], direction (0 is forward) [0/1], enable [0/1]
void walk(float period, int steps, int direction, int enable){
  float group1;
  float group2;
  float group1Hip;
  float group2Hip;
  float group1Knee;
  float group2Knee;
  float group1Foot;
  float group2Foot;
  if(direction == 1){
    for(int i = 0; i <= 2 * steps; i++){
      int hStep = steps/2;

      //calculate hip angles
      group1 = hStep + hStep * cos(2 * 3.14 * i / (2*steps));
      group2 = hStep + hStep * cos((2 * 3.14 * i / (2*steps)) + 3.14);

      group1Hip = group1;
      group2Hip = group2;

      //calculate knee angles
      if((i % (2 * steps)) < steps){
        group1Knee = 180;
        group2Knee = 180 - 2 *(hStep + hStep * cos((2 * 3.14 * i / steps) + 3.14));
      }
      else{
        group1Knee = 180 - 2 * (hStep + hStep * cos((2 * 3.14 * i / steps) + 3.14));
        group2Knee = 180;
      }
      
      //calculate foot angles
      if(group1Knee == 180){
        group1Foot = 0;
        group2Foot = 180 - group2Knee;
      }
      else{
        group1Foot = 180 - group1Knee;
        group2Foot = 0;
      }
      if(enable == 1){
        //upper limbs
        move11(group1Hip + 30);
        move21(group2Hip + 30);
        move31(group1Hip + 55);

        move61(-1 * group2Hip - 30);
        move51(-1 * group1Hip - 30);
        move41(-1 * group2Hip - 55);

        //middle limbs
        move12(group1Knee);
        move22(group2Knee);
        move32(group1Knee);

        move62(-1 * group2Knee);
        move52(-1 * group1Knee);
        move42(-1 * group2Knee);

        //end limbs        
        move13(-1 * group1Foot + 110);
        move23(-1 * group2Foot + 110);
        move33(-1 * group1Foot + 110);

        move63(group2Foot - 110);
        move53(group1Foot - 110);
        move43(group2Foot - 110);
      }
      delay(float(1000 * period * period / steps));
      //debug info
      // Serial.print("i: ");
      // Serial.print(i);
      // Serial.print(" , group1: ");
      // Serial.print(group1);
      // Serial.print(" , group2: ");
      // Serial.print(group2);
      // Serial.print(" , group1Knee: ");
      // Serial.print(group1Knee);
      // Serial.print(" , group2Knee: ");
      // Serial.print(group2Knee);
      // Serial.print(" , group1Foot: ");
      // Serial.print(group1Foot);
      // Serial.print(" , group2Foot: ");
      // Serial.println(group2Foot);
    }
  }

  else if(direction == 0){
    for(int i = 2*steps; i >=0; i--){
      int hStep = steps/2;

      //calculate hip angles
      group1 = hStep + hStep * cos(2 * 3.14 * i / (2*steps));
      group2 = hStep + hStep * cos((2 * 3.14 * i / (2*steps)) + 3.14);

      group1Hip = group1;
      group2Hip = group2;

      //calculate knee angles
      if((i % (2 * steps)) < steps){
        group1Knee = 180;
        group2Knee = 180 - 2 *(hStep + hStep * cos((2 * 3.14 * i / steps) + 3.14));
      }
      else{
        group1Knee = 180 - 2 * (hStep + hStep * cos((2 * 3.14 * i / steps) + 3.14));
        group2Knee = 180;
      }
      
      //calculate foot angles
      if(group1Knee == 180){
        group1Foot = 0;
        group2Foot = 180 - group2Knee;
      }
      else{
        group1Foot = 180 - group1Knee;
        group2Foot = 0;
      }
      if(enable == 1){
        //upper limbs
        move11(group1Hip + 30);
        move21(group2Hip + 30);
        move31(group1Hip + 55);

        move61(-1 * group2Hip - 30);
        move51(-1 * group1Hip - 30);
        move41(-1 * group2Hip - 55);

        //middle limbs
        move12(group1Knee);
        move22(group2Knee);
        move32(group1Knee);

        move62(-1 * group2Knee);
        move52(-1 * group1Knee);
        move42(-1 * group2Knee);

        //end limbs        
        move13(-1 * group1Foot + 110);
        move23(-1 * group2Foot + 110);
        move33(-1 * group1Foot + 110);

        move63(group2Foot - 110);
        move53(group1Foot - 110);
        move43(group2Foot - 110);
      }
      delay(float(1000 * period * period / steps));
      //debug info
      // Serial.print("i: ");
      // Serial.print(i);
      // Serial.print(" , group1: ");
      // Serial.print(group1);
      // Serial.print(" , group2: ");
      // Serial.print(group2);
      // Serial.print(" , group1Knee: ");
      // Serial.print(group1Knee);
      // Serial.print(" , group2Knee: ");
      // Serial.print(group2Knee);
      // Serial.print(" , group1Foot: ");
      // Serial.print(group1Foot);
      // Serial.print(" , group2Foot: ");
      // Serial.println(group2Foot);
    }
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
  joint[11].write(155 + pos);
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