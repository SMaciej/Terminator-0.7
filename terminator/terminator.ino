#include <Fuzzy.h>
#include <FuzzyComposition.h>
#include <FuzzyInput.h>
#include <FuzzyIO.h>
#include <FuzzyOutput.h>
#include <FuzzyRule.h>
#include <FuzzyRuleAntecedent.h>
#include <FuzzyRuleConsequent.h>
#include <FuzzySet.h>
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
int leftIR = 13;
int rightIR = 12;
// ultrasonic sensors
int middleEyeTrigger = 8;
int middleEye = 4;
int leftEyeTrigger = 3;
int leftEye = 2;
int rightEye = 15;
int rightEyeTrigger = 16;

// GLOBAL VARIABLES
// bluetooth signal
char bt_signal;
char btx;
Fuzzy* fuzzy = new Fuzzy();
int test = 0;


void setup() {
  // FUNCTION CALLED ON RESET
  
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
  //Serial.begin(9600);    // uncomment that for Serial to work
  // set bluetooth serial
  //BT.begin(9600);        // uncomment that for BT to work
  BT.println("Terminator 0.7 connected.");
  
  // ZBIORY ROZMYTE
  
  // odleglosc na sensorze srodkowym
  FuzzyInput* distance = new FuzzyInput(1);
  //
  FuzzySet* big = new FuzzySet(15,30,30,30);
  distance->addFuzzySet(big);
  FuzzySet* average = new FuzzySet(0,15,15,30);
  distance->addFuzzySet(average);
  FuzzySet* small = new FuzzySet(0,0,0,15);
  distance->addFuzzySet(small);
  //
  fuzzy->addFuzzyInput(distance);

  // odleglosc na sensorze lewym
  FuzzyInput* distance2 = new FuzzyInput(2);
  //
  FuzzySet* big2 = new FuzzySet(15,30,30,30);
  distance2->addFuzzySet(big2);
  FuzzySet* average2 = new FuzzySet(0,15,15,30);
  distance2->addFuzzySet(average2);
  FuzzySet* small2 = new FuzzySet(0,0,0,15);
  distance2->addFuzzySet(small2);
  //
  fuzzy->addFuzzyInput(distance2);
  
  // predkosc
  FuzzyOutput* speed = new FuzzyOutput(1);
  //
  FuzzySet* slow = new FuzzySet(70,120,120,120);
  speed->addFuzzySet(slow);
  FuzzySet* mild = new FuzzySet(100,125,125,150);
  speed->addFuzzySet(mild);
  FuzzySet* fast = new FuzzySet(125,230,230,230);
  speed->addFuzzySet(fast);
  //
  fuzzy->addFuzzyOutput(speed);

  // obrot (jak duzy powinien byc, tzn czas trwania)
  FuzzyOutput* turn = new FuzzyOutput(2);
  //
  FuzzySet* small_turn = new FuzzySet(300,600,600,600);
  turn->addFuzzySet(small_turn);
  FuzzySet* mild_turn = new FuzzySet(300,500,500,1100);
  turn->addFuzzySet(mild_turn);
  FuzzySet* fast_turn = new FuzzySet(500,1500,1500,1500);
  turn->addFuzzySet(fast_turn);
  //
  fuzzy->addFuzzyOutput(turn);

  // ZASADY LOGIKI ROZMYTEJ
  
  // zasada pierwsza
  FuzzyRuleAntecedent* middleSmallAndLeftSmall = new FuzzyRuleAntecedent();
  middleSmallAndLeftSmall->joinWithAND(small,small2);
  FuzzyRuleConsequent* DoATurn= new FuzzyRuleConsequent();
  DoATurn->addOutput(small_turn);
  //
  FuzzyRule* fuzzyRule01 = new FuzzyRule(1, middleSmallAndLeftSmall, DoATurn);
  fuzzy->addFuzzyRule(fuzzyRule01);
  
  // zasada druga
  FuzzyRuleAntecedent* middleBigAndLeftBig = new FuzzyRuleAntecedent();
  middleBigAndLeftBig->joinWithAND(big,big2);
  FuzzyRuleConsequent* GoForwardFast= new FuzzyRuleConsequent();
  GoForwardFast->addOutput(fast);
  //
  FuzzyRule* fuzzyRule02 = new FuzzyRule(1, middleBigAndLeftBig, GoForwardFast);
  fuzzy->addFuzzyRule(fuzzyRule02);

  // zasada trzecia
  FuzzyRuleAntecedent* middleMediumAndLeftMedium = new FuzzyRuleAntecedent();
  middleMediumAndLeftMedium->joinWithAND(average,average2);
  FuzzyRuleConsequent* GoMediumFast= new FuzzyRuleConsequent();
  GoMediumFast->addOutput(mild);
  //
  FuzzyRule* fuzzyRule03 = new FuzzyRule(1, middleMediumAndLeftMedium, GoMediumFast);
  fuzzy->addFuzzyRule(fuzzyRule03);
  
}


void listen_bluetooth() {
  if (BT.available()) {
    bt_signal = (BT.read());
    if (bt_signal == '0') {
      motorsOff();
    }
    while (bt_signal == 'F') {
      // drive forward
      btx = (BT.read());
      motorsForward(0, 140);
      if (btx == '0') {
        break;
      }
    }
    while (bt_signal == 'B') {
      // drive backward
      btx = (BT.read());
      motorsBackward(1000, 140);
      if (btx == '0') {
        break;
      }
    }
    while (bt_signal == 'L') {
      // turn left
      btx = (BT.read());
      motorsTurnLeft(500, 140);
      if (btx == '0') {
        break;
      }
    } 
    while (bt_signal == 'R') {
      // turn right
      btx = (BT.read());
      motorsTurnRight(500, 140);
      if (btx == '0') {
        break;
      }
    }
    while (bt_signal == 'T') {
      // line-tracking
      btx = (BT.read());
      line_tracking();
      if (btx == '0') {
        break;
      }
    }
    if (bt_signal == 'S') {
      // ultrasonic sensors
    }
  }
}


void loop() {
  line_tracking();
}
