void setup() {
  // Initialize serial communication at 9600 baud
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  /*if (Serial.available() > 0) {

    int incomingData = Serial.read();
    digitalWrite(LED_BUILTIN,HIGH);
    
  }*/
  Serial.println("Hello");
}
