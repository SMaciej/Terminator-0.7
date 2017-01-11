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
int right2;
int left2;

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

int limit(int value, int sensor)
{
  /*
    while ( value == 0)
    {
    if ( sensor == 1)
    {
      value = middleEye.ping_cm();
    }
    if ( sensor == 2)
    {
      value = leftEye.ping_cm();
    }
    if ( sensor == 3)
    {
      value = rightEye.ping_cm();
    }
    }
  */
  if ( value > 60)
  {
    value = 60;
  }
  if ( value == 0)
  {
    value = 60;
  }
  return value;
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
      if( limit(middleEye.ping_cm(), 1) >= 30)
      {
        motorsForward(0, 250);
      }
      else
      {
        if ( limit(middleEye.ping_cm(), 1) >=15)
        {
          motorsForward(0, 150);
        }
        else
        {
          if ( limit(middleEye.ping_cm(), 1) >=5 )
          {
            motorsForward(0,100);
          }
          else
          {
            
          }
        }
      }
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

  //listen_bluetooth();
  ultrasonic_sensors();
  
  }
  



