int x;
int y;

void setup() {
  Serial.begin(9600);

}

void loop() {
  if(digitalRead(3) == LOW && digitalRead(5) == LOW){
    Serial.print("center ");
  }
  else if(digitalRead(3) == HIGH && digitalRead(5) == LOW){
    Serial.print("left ");
  }
  else{
    Serial.print("right ");
  }

  if(digitalRead(6) == LOW && digitalRead(7) == LOW){
    Serial.println("center ");
  }
  else if(digitalRead(6) == HIGH && digitalRead(7) == LOW){
    Serial.println("down ");
  }
  else{
    Serial.println("up");
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
