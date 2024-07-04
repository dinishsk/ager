#include <AccelStepper.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>


//GPS Object Creation
TinyGPSPlus gps;


//NPK Sensor Pins and Initialzation
SoftwareSerial mod(50,51);

#define RE 52
#define DE 53

byte values[11];
const byte nitro[] = {0x01,0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const byte phos[] = {0x01,0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte pota[] = {0x01,0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};


//Drive Motors Pins
int ena = 4;
int in1 = 5;
int in2 = 6;
int in3 = 7;
int in4 = 8;
int enb = 9;

//For Synchronous Transfer of GPS Data
unsigned long previousMillis = 0;
const long interval = 2000;  //Trasfer Data at every 2S

//Stepper Motor
int dirPin = 2;
int stepPin = 3;
#define motorInterfaceType 1

AccelStepper myStepper(motorInterfaceType, stepPin, dirPin);


void setup()
{
  //Serial Monitor
  Serial.begin(9600);

  //Lora
  Serial2.begin(9600);
  
  //GPS
  Serial3.begin(9600);
  
  //Drive Motor
  pinMode(ena,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(enb,OUTPUT);
  analogWrite(ena,240);  
  analogWrite(enb,240);  //Set Speed to 240

  //Stepper Motor
  myStepper.setMaxSpeed(200);
	myStepper.setAcceleration(50);
	myStepper.setSpeed(200);
  pinMode(10,OUTPUT);
  digitalWrite(48,HIGH);  // Initially Disable the Stepper Motor

  //NPK Sensor
  mod.begin(9600);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
}

void loop()
{
  //For reading the Control commands from LoRa
  char a = 'm';     //Initially Stop Everything
  while(Serial2.available()>0)
  {
    a = (char) Serial2.read();
    Serial.print(a);
  }

  //Control Calling
  control(a);

  //Transfer of GPS data to the Controller at every Interval
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      while (Serial3.available() > 0) {
        if (gps.encode(Serial3.read())) {   //Reading GPS Data
          if (gps.location.isValid()) {
            Serial2.println("g,"+String(gps.location.lat(),6)+","+String(gps.location.lng(),6));  //Transfer the Data to the Controller
          }
          else {
          Serial2.println("g,"+String(0)+","+String(0));
          }
        }
      }
  }
}

//Motor Control
void control(char input)
{
  switch(input)
  {
    case 'w':   //Forward
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
      break;
    case 's':   //Reverse
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);
      break;
    case 'd':   //Right
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);
      break;
    case 'a':    //Left
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
      break;
    case 'm':   //Stop
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
      break;
    case 'l':   //For Collecting Data
      myStepper.move(-2100);      //Give the Distance that the Stepper motor goes Down
      digitalWrite(48,LOW);       //Enable Stepper Motor
      while(myStepper.isRunning()){
        myStepper.run();          //Running Stepper Motor
      }
      digitalWrite(48,HIGH);      //Again Disable the Stepper Motor

      //Collecting the data
      byte val1,val2,val3;
      int c=5;
      while(c){
        val1 = nitrogen();
        delay(250);
        val2 = phosphorous();
        delay(250);
        val3 = potassium();
        delay(250);
        c-=1;
      }

      Serial2.println("n,"+String(val1)+","+String(val2)+","+String(val3));    //Sending the Data to the Controller
    
      myStepper.move(2200);         //Give the Distance that the Stepper motor goes Up
      digitalWrite(48,LOW);         //Enable the Stepper Motor
      while(myStepper.isRunning()){
        myStepper.run();            //Running the Stepper Motor
      }
      digitalWrite(48,HIGH);        //Disable the Stepper Motor
      
      Serial2.println("k");         //Giving the Feedback Signal to the Controller
  }
}

//Nitrogen Data Collection from NPK
byte nitrogen(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(nitro,sizeof(nitro))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(mod.read(),HEX);
    values[i] = mod.read();
    Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}
 

//Phosphorous Data Collection from NPK
byte phosphorous(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(phos,sizeof(phos))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(mod.read(),HEX);
    values[i] = mod.read();
    Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}
 

//Potassium Data Collection from NPK
byte potassium(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(pota,sizeof(pota))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(mod.read(),HEX);
    values[i] = mod.read();
    Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}