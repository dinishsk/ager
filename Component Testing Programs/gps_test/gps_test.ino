#include <TinyGPS++.h>

TinyGPSPlus gps;


void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  pinMode(48,OUTPUT);
  digitalWrite(48,HIGH);
}

void loop() {
  if (Serial3.available() > 0) {
    if (gps.encode(Serial3.read())) {
      if (gps.location.isValid()) {
        Serial.println("g,"+String(gps.location.lat(),6)+","+String(gps.location.lng(),6));
      }
      else {
      Serial.println("g,"+String(0)+","+String(0));
        }
      }
    }
  }