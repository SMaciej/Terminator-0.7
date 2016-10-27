// motor one
int enA = 0;
int in1 = 1;
int in2 = 2;
// motor two
int enB = 5;
int in3 = 3;
int in4 = 4;
// IR sensors
int leftIR = 13;
int rightIR = 12;

void setup() {
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  // set serial
  Serial.begin(9600);

}

void motorsOff() {
  // turn all the motors off
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);  
}
  

void motorsForward(int period, int power) {
  // run all the motors in a forward direction
  
  // turn on motors
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  // set motors speed
  analogWrite(enA, power-90);
  analogWrite(enB, power);
  
  delay(period);
  
  motorsOff();
  

}

void motorsBackward(int period, int power) {
  // run all the motors in a backward direction
  
  // turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
  // set motors speed
  analogWrite(enA, power-90);
  analogWrite(enB, power);
  
  delay(period);
  
  motorsOff();
}

void motorsTurnRight(int period, int power) {
  // run the left motors only
  
  // turn on motors
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  // set motors speed
  analogWrite(enA, power-90);
  
  delay(period);
  
  motorsOff();
}

void motorsTurnLeft(int period, int power) {
  // run the right motors only
  
  // turn on motors
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  // set motors speed
  analogWrite(enB, power);
  
  delay(period);
  
  motorsOff();
}

int IRleft() {
  // returns left IR value
  return digitalRead(leftIR);
}

int IRright() {
  // return right IR value
  return digitalRead(rightIR);
}


void loop() {
  motorsForward(2000, 250);
  motorsBackward(2000, 250);
  motorsTurnLeft(2000,250);
  motorsTurnRight(2000, 250);
  delay(3000);
}
