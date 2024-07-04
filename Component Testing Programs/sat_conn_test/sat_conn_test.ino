#include <SoftwareSerial.h>

// The serial connection t

void setup(){
  Serial.begin(9600);
  Serial3.begin(9600);
  pinMode(48,OUTPUT);
  digitalWrite(48,HIGH);
}

void loop(){
  while (Serial3.available() > 0){
    // get the byte data from the GPS
    byte gpsData = Serial3.read();
    Serial.write(gpsData);
  }
}