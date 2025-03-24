int motor1pin1 = 5;
int motor1pin2 = 6;
int ENA = 9;

void setup() {
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(ENA, OUTPUT);
  analogWrite(motor1pin1, 0);
  
  analogWrite(motor1pin2, 0);
}

void loop() {
//  analogWrite(ENA, 100);
  
  analogWrite(motor1pin1, 255);
  analogWrite(motor1pin2, 0);
  delay(3000);

  analogWrite(motor1pin1, 0);
  analogWrite(motor1pin2, 0);
  delay(3000);

  analogWrite(motor1pin1, 0);
  analogWrite(motor1pin2, 255);
  delay(3000);

  
}
