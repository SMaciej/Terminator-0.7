// LINE TRACKING FUNCTIONS AND ALGORITHMS


int IRleft() {
  return digitalRead(leftIR);
}


int IRright() {
  return digitalRead(rightIR);
}


void line_tracking() {
  // main line tracking function
  if(IRleft() == 1 && IRright() == 1) {
    motorsForward(10,85);
  }
  if(IRleft() == 0 && IRright() == 1) {
    motorsTurnRight(30,140);
  }
  if(IRleft() == 1 && IRright() == 0) {
    motorsTurnLeft(30,140);
  }
  if(IRleft() == 0 && IRright() == 0) {
    motorsForward(10,85);
  }
}

