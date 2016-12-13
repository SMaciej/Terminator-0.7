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
    motorsTurnRight(10,120);
  }
  if(IRleft() == 1 && IRright() == 0) {
    motorsTurnLeft(10,120);
  }
  if(IRleft() == 0 && IRright() == 0) {
    motorsForward(10,85);
  }
}



void line_tracking_fast() {
  // faster version of line tracking function
  if(IRleft() == 1 && IRright() == 1) {
    motorsForward(4,180);
  }
  if(IRleft() == 0 && IRright() == 1) {
    motorsTurnRight(6,125);
  }
  if(IRleft() == 1 && IRright() == 0) {
    motorsTurnLeft(6,125);
  }
  if(IRleft() == 0 && IRright() == 0) {
    motorsForward(4,180);
  }
}


void line_tracking_turbo() {
  // main line tracking function
  // sensors should be widen up for this one
  // highly experimental
  // wear protective gear
  // surveillance of at least three person team needed
  if(IRleft() == 1 && IRright() == 1) {
    motorsForward(5,220);
  }
  if(IRleft() == 0 && IRright() == 1) {
    motorsTurnRight(5,255);
  }
  if(IRleft() == 1 && IRright() == 0) {
    motorsTurnLeft(5,255);
  }
  if(IRleft() == 0 && IRright() == 0) {
    motorsForward(5,220);
  }
}
