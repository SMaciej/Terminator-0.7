// MOTORS CONTROL FUNCTIONS


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
  
  // if period is 0 motors will run for an unlimited period of time
  if (period != 0) { 
    delay(period);    
  }
  
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
  
  // if period is 0 motors will run for an unlimited period of time
  if (period != 0) { 
    delay(period);    
  }
  
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
  
  // if period is 0 motors will run for an unlimited period of time
  if (period != 0) { 
    delay(period);    
  }
  
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
  
  // if period is 0 motors will run for an unlimited period of time
  if (period != 0) { 
    delay(period);    
  }
  
  motorsOff();
}

