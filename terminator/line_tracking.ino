// LINE TRACKING FUNCTIONS AND ALGORITHMS


int IRleft() {
  return digitalRead(leftIR);
}


int IRright() {
  return digitalRead(rightIR);
}


int IRcenter() {
  return digitalRead(centerIR);
}

void line_tracking() {
    while(IRleft() == 1 && IRcenter() == 0 && IRright() == 1) {
      btx = (BT.read());
      if (btx == 'O') {
        break;
      }
      motorsForward(0,90);
    }
    while(IRleft() == 1 && IRcenter() == 1 && IRright() == 1) {
      btx = (BT.read());
      if (btx == 'O') {
        break;
      }
      motorsForward(0,90);
    }
    while(IRleft() == 1 && IRcenter() == 1 && IRright() == 0) {
      btx = (BT.read());
      if (btx == 'O') {
        break;
      }
      motorsTurnRight(0,160);
    }
    while(IRleft() == 0 && IRcenter() == 1 && IRright() == 1) {
      btx = (BT.read());
      if (btx == 'O') {
        break;
      }
      motorsTurnLeft(0,160);
    }
    while(IRleft() == 0 && IRcenter() == 0 && IRright() == 1) {
      btx = (BT.read());
      if (btx == 'O') {
        break;
      }
      motorsTurnLeft(0,200);
    }
    while(IRleft() == 1 && IRcenter() == 0 && IRright() == 0) {
      btx = (BT.read());
      if (btx == 'O') {
        break;
      }
      motorsTurnRight(0,200);
    }
    while(IRleft() == 0 && IRcenter() == 0 && IRright() == 0) {
      btx = (BT.read());
      if (btx == 'O') {
        break;
      }
      motorsOff();
    }
}


