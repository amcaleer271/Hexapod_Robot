#include <SoftwareSerial.h>

SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin
int sendMsg;

void setup() {
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC12

}

void loop() {
  //Serial.print(" ");
  //Serial.println(analogRead(A2));
  sendMsg = 100 * map(analogRead(A2),0, 1024, 10, 99) + map(analogRead(A4),0, 1024, 10, 99);
  HC12.println(sendMsg);
  Serial.println(sendMsg);

}



