#include <SoftwareSerial.h>

SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin

int msg;
int y;
int x;
void setup() {
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC12
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {

  while (HC12.available()) {        // If HC-12 has data
    msg = HC12.parseInt();
    x = msg/ 100;
    y = msg - (msg / 100)*100;
    Serial.print(x);
    Serial.print(" ");
    Serial.println(y);
    if(x < 65 && x > 45){
      digitalWrite(3, LOW);
      digitalWrite(5, LOW);
    }
    else if(x > 65){
      digitalWrite(3, HIGH);
      digitalWrite(5, LOW);
    }
    else{
      digitalWrite(3, HIGH);
      digitalWrite(5, HIGH);
    }

    if(y < 65 && y > 45){
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
    }
    else if(y > 65){
      digitalWrite(6, HIGH);
      digitalWrite(7, LOW);
    }
    else{
      digitalWrite(6, HIGH);
      digitalWrite(7, HIGH);
    }
  }
}