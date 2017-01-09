#include <Fuzzy.h>
#include <FuzzyComposition.h>
#include <FuzzyInput.h>
#include <FuzzyIO.h>
#include <FuzzyOutput.h>
#include <FuzzyRule.h>
#include <FuzzyRuleAntecedent.h>
#include <FuzzyRuleConsequent.h>
#include <FuzzySet.h>
#include <NewPing.h>
#include<SoftwareSerial.h>
SoftwareSerial BT(1, 0);


// PORTS DEFINITIONS
// motor one
int enA = 9;
int in1 = 10;
int in2 = 11;
// motor two
int enB = 5;
int in3 = 6;
int in4 = 7;
// IR sensors
int leftIR = 15;
int rightIR = 14;
int centerIR = 16;
// ultrasonic sensors
int middleEyeTrigger = 8;
int middleEyeEcho = 4;
int leftEyeTrigger = 3;
int leftEyeEcho = 2;
int rightEyeEcho = 12;
int rightEyeTrigger = 13;
int turnTest = 0;
int right;
int left;

// GLOBAL VARIABLES
// bluetooth signal
char bt_signal;
char btx;
Fuzzy* fuzzy = new Fuzzy();
int test = 0;
// ultrasonic sensors
NewPing leftEye(leftEyeTrigger, leftEyeEcho, 100);
NewPing middleEye(middleEyeTrigger, middleEyeEcho, 100);
NewPing rightEye(rightEyeTrigger, rightEyeEcho, 100);


void setup() {
  // FUNCTION CALLED ON RESET
  
  // set all the control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // set serial
  Serial.begin(9600);    // uncomment that for Serial to work
  
  // set bluetooth serial
  //BT.begin(9600);        // uncomment that for BT to work
  //BT.println("Terminator 0.7 connected.");
  
  fuzzy_rules();
  
}


void listen_bluetooth() {
  if (BT.available()) {
    bt_signal = (BT.read());
    if (bt_signal == 'O') {
      motorsOff();
    }
    while (bt_signal == 'F') {
      // drive forward
      btx = (BT.read());
      motorsForward(0, 250);
      if (btx == 'O') {
        motorsOff();
        break;
      }
    }
    while (bt_signal == 'B') {
      // drive backward
      btx = (BT.read());
      motorsBackward(0, 250);
      if (btx == 'O') {
        motorsOff();
        break;
      }
    }
    while (bt_signal == 'L') {
      // turn left
      btx = (BT.read());
      motorsTurnLeft(0, 200);
      if (btx == 'O') {
        motorsOff();
        break;
      }
    } 
    while (bt_signal == 'R') {
      // turn right
      btx = (BT.read());
      motorsTurnRight(0, 200);
      if (btx == 'O') {
        motorsOff();
        break;
      }
    }
    while (bt_signal == 'A') {
      // line-tracking
      btx = (BT.read());
      line_tracking();
      if (btx == 'O') {
        motorsOff();
        break;
      }
    }
    while (bt_signal == 'S') {
      // ultrasonic sensors
      btx = (BT.read());
      ultrasonic_sensors();
      if (btx == 'O') {
        motorsOff();
        break;
      }
    }
  }
}


void loop() {

  listen_bluetooth();
  //ultrasonic_sensors();
  
  }
  



