// motor one
int enA = 9;
int in1 = 10;
int in2 = 11;
// motor two
int enB = 5;
int in3 = 6;
int in4 = 7;
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
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  // set motors speed
  analogWrite(enA, power);
  analogWrite(enB, power);
  
  delay(period);
  
  motorsOff();
  

}

void motorsBackward(int period, int power) {
  // run all the motors in a backward direction
  
  // turn on motors
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
  // set motors speed
  analogWrite(enA, power);
  analogWrite(enB, power);
  
  delay(period);
  
  motorsOff();
}

void motorsTurnRight(int period, int power) {
  // run the left motors only
  
  // turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  // set motors speed
  analogWrite(enA, power);
  analogWrite(enB, power);
  
  delay(period);
  
  motorsOff();
}

void motorsTurnLeft(int period, int power) {
  // run the right motors only
  
  // turn on motors
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  // set motors speed
  analogWrite(enA, power);
  analogWrite(enB, power);
  
  delay(period);
  
  motorsOff();
}

int IRleft() {
  return digitalRead(leftIR);
}

int IRright() {
  return digitalRead(rightIR);
}


void loop() {
  motorsOff();
  delay(3000);
  motorsForward(2000,100);
  motorsTurnLeft(700,140);
  motorsForward(2000,100);
  motorsTurnLeft(700,140); 
  motorsForward(1000,250);
  motorsBackward(1000,250); 
  //Serial.println(IRleft()); // print the data from the left sensor
}
