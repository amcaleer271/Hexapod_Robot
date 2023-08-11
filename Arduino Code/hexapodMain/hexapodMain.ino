#include <Servo.h>

Servo joint[25]; 
int voltagePin = 3;
int led = 7;
int isTurning;

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

class Leg{
    private:
      int joints[3];
      int offsets[3];

    public:
      Leg(int joint1, int joint2, int joint3, int offset1, int offset2, int offset3){
        joints[1] = joint1;
        joints[2] = joint2;
        joints[3] = joint3;
        offsets[1] = offset1;
        offsets[2] = offset2;
        offsets[3] = offset3;
      }

      void moveLeg(int pos1, int pos2, int pos3){
        joint[joints[1]].write(pos1 + offsets[1]);
        joint[joints[2]].write(pos2 + offsets[2]);
        joint[joints[3]].write(pos3 + offsets[3]);
      }
  };
  
//create legs (joint1, joint2, joint3, offset1, offset2, offset3)
  Leg leg1(24,23,22,120,0,0);
  Leg leg2(21,20,19,50,10,20);
  Leg leg3(18,17,16,100,5,20);
  Leg leg4(7,8,11,90,170,155);
  Leg leg5(4,5,6,90,170,158);
  Leg leg6(1,2,3,85,177,185);
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

int radioDecode(){
  //convert the binary signals from the recieving arduino into an integer 1-9
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

void checkBattery(){
  //checks battery voltage is above 12.4v
  if(analogRead(voltagePin) < 840){
    for(int i = 0; i<=3; i++){
      delay(1000);
      digitalWrite(led, LOW);
      delay(1000);
      digitalWrite(led, HIGH);
    }
  }
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
      leg1.moveLeg(1.1*group1Hip + 30, group1Knee, -1 * group1Foot + 110);
      leg2.moveLeg(1.1*group2Hip + 30, group2Knee, -1 * group2Foot + 110);
      leg3.moveLeg(1.1*group1Hip + 55, group1Knee, -1 * group1Foot + 110);
      leg4.moveLeg(30 - 1.1*group1Hip, -1 * group2Knee, group2Foot - 110);
      leg5.moveLeg(30 - 1.1*group2Hip, -1 * group1Knee, group1Foot - 110);
      leg6.moveLeg(30 - 1.1*group1Hip, -1 * group2Knee, group2Foot - 110);
    }
    else{

      leg1.moveLeg(1.1*group1Hip + 30, group1Knee, -1 * group1Foot + 110);
      leg2.moveLeg(1.1*group2Hip + 30, group2Knee, -1 * group2Foot + 110);
      leg3.moveLeg(1.1*group1Hip + 55, group1Knee, -1 * group1Foot + 110);
      leg4.moveLeg(-1 * 0.7*group2Hip - 55, -1 * group2Knee, group2Foot - 110);
      leg5.moveLeg(-1 * 0.7*group1Hip - 30, -1 * group1Knee, group1Foot - 110);
      leg6.moveLeg(-1 * 0.7*group2Hip - 30, -1 * group2Knee, group2Foot - 110);
    }
  }
}
