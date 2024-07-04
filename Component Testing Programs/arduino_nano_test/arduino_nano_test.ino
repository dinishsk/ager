#include <SoftwareSerial.h>

SoftwareSerial lora(2,3);

void setup()
{
  Serial.begin(9600);
  lora.begin(9600);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
}

void loop()
{
  while(lora.available()>0)
  {
    char a = (char) lora.read();
    Serial.write(a);
  }
  while(Serial.available()>0)
  {
    char a = (char) Serial.read();
    lora.write(a);
  }
}
