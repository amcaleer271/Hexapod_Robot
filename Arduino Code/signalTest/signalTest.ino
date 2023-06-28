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
