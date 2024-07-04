#include <SoftwareSerial.h>

//Initialize the LoRa
SoftwareSerial lora(2,3);

void setup()
{
  //Serial Monitor
  Serial.begin(9600);

  //LoRa
  lora.begin(9600);
  
  //Modes Setting for Bidirectional
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
}

void loop()
{
  //For Reading Data 
  while(lora.available()>0)
  {
    char a = (char) lora.read();    //Read from LoRa
    Serial.write(a);      //Writing in Serial for Python Program
  }

  //For Writting data
  while(Serial.available()>0)
  {
    char a = (char) Serial.read();    //Reading from Serial for Python Programming
    lora.write(a);        //Writting to LoRa
  }
}
