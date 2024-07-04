#include <AccelStepper.h>

int dirPin = 2;
int stepPin = 3;

#define motorInterfaceType 1

AccelStepper myStepper(motorInterfaceType, stepPin, dirPin);

void setup() {
	Serial.begin(9600);
  myStepper.setMaxSpeed(100);
	myStepper.setAcceleration(20);
	myStepper.setSpeed(100);
  pinMode(10,OUTPUT);
  digitalWrite(48,HIGH);
}

void loop() {
  int a = Serial.read();
  Serial.println(a);
  stepperMotorControl(a);
}
void stepperMotorControl(char a)
{
  switch(a)
  {
    case 'u':
      myStepper.move(2200);
      digitalWrite(48,LOW);
      while(myStepper.isRunning()){
        myStepper.run();
      }
      digitalWrite(48,HIGH);
      break;
    case 'i':
      myStepper.move(-2100);
      digitalWrite(48,LOW);
      while(myStepper.isRunning()){
        myStepper.run();
      }
      digitalWrite(48,HIGH);
      break;
      
  }
}