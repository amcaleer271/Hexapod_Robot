#include <SoftwareSerial.h>

SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin

int speed = 0;
int msg;
int y;
int x;
void setup() {
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC12

}

void loop() {

  while (HC12.available()) {        // If HC-12 has data
    msg = HC12.parseInt();
    x = msg/ 100;
    y = msg - int(msg / 100)*100;
    Serial.print(x);
    Serial.print(" ");
    Serial.println(y);
  }

  
  while (Serial.available()) {      // If Serial monitor has data
    HC12.write(Serial.read());      // Send that data to HC-12
  }

}