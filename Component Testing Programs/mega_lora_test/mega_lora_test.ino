void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600);
}

void loop()
{
  while(Serial2.available()>0)
  {
    char a = (char) Serial2.read();
    Serial.print(a);
  }
  while(Serial.available()>0)
  {
    char a = (char) Serial.read();
    Serial2.write(a);
  }
}
