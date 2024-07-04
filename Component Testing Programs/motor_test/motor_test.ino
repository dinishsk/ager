int ena = 4;
int in1 = 5;
int in2 = 6;
int in3 = 7;
int in4 = 8;
int enb = 9;

void setup()
{
  Serial.begin(9600);
  pinMode(ena,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(enb,OUTPUT);
  analogWrite(ena,230);
  analogWrite(enb,230);
}

void loop()
{
  int a = Serial.read();
  Serial.println(a);
  motorcontrol(a);
}

void motorcontrol(char input)
{
  switch(input)
  {
    case 'w':
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
      delay(100);
      break;
    case 's':
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);
      delay(100);
      break;
    case 'd':
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);
      delay(100);
      break;
    case 'a':
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
      delay(100);
    
    default:
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
  }
}