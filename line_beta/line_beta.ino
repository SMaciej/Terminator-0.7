#include<SoftwareSerial.h>
SoftwareSerial BT(1, 0);

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
// ultrasonic sensors
int middleEyeTrigger = 8;
int middleEye = 4;
int leftEyeTrigger = 3;
int leftEye = 2;
int rightEye = 15;
int rightEyeTrigger = 16;
// bluetooth signal
char bt_signal;

void setup() {
  // set all the control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(middleEye,OUTPUT);
  pinMode(leftEye,OUTPUT);
  pinMode(rightEye,OUTPUT);
  // set serial
  //Serial.begin(9600);
  // set bluetooth serial
  BT.begin(9600);
  BT.println("Terminator 0.7 connected.");
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

void line_tracking() {
  if(IRleft() == 1 && IRright() == 1) {
    motorsForward(10,85);
  }
  if(IRleft() == 0 && IRright() == 1) {
    motorsTurnRight(10,130);
  }
  if(IRleft() == 1 && IRright() == 0) {
    motorsTurnLeft(10,130);
  }
  if(IRleft() == 0 && IRright() == 0) {
    motorsForward(10,85);
  }
}

void listen_bluetooth() {
  if (BT.available()) {
    bt_signal = (BT.read());
    if (bt_signal == '0') {
      motorsOff();
    }
    if (bt_signal == 'F') {
      // drive forward
      motorsForward(1000, 140);
    }
    if (bt_signal == 'B') {
      // drive backward
      motorsBackward(1000, 140);
    }
    if (bt_signal == 'L') {
      // turn left
      motorsTurnLeft(500, 140);
    } 
    if (bt_signal == 'R') {
      // turn right
      motorsTurnRight(500, 140);
    }
    if (bt_signal == 'T') {
      // line-tracking
      line_tracking();
    }
  }
}

unsigned long ping(int ultraSoundSignal) {
  unsigned long echo = 0;
  unsigned long ultrasoundValue = 0;
  pinMode(ultraSoundSignal, OUTPUT); // Switch signalpin to output
  digitalWrite(ultraSoundSignal, LOW); // Send low pulse
  delayMicroseconds(2); // Wait for 2 microseconds
  digitalWrite(ultraSoundSignal, HIGH); // Send high pulse
  delayMicroseconds(5); // Wait for 5 microseconds
  digitalWrite(ultraSoundSignal, LOW); // Holdoff
  pinMode(ultraSoundSignal, INPUT); // Switch signalpin to input
  digitalWrite(ultraSoundSignal, HIGH); // Turn on pullup resistor
  // please note that pulseIn has a 1sec timeout, which may
  // not be desirable. Depending on your sensor specs, you
  // can likely bound the time like this -- marcmerlin
  // echo = pulseIn(ultraSoundSignal, HIGH, 38000)
  echo = pulseIn(ultraSoundSignal, HIGH); //Listen for echo
  ultrasoundValue = (echo / 58.138); //convert to CM then to inches
  return ultrasoundValue;
}

void ultrasonic_values() {
   int x = 0;
   int y = 0;
   int z = 0;
   y = ping(middleEye);
   x = ping(leftEye);
   z = ping(rightEye);
   Serial.println(x);
   delay(300); //delay 1/4 seconds.
}

void loop() {
  listen_bluetooth();
}
