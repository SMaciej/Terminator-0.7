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
int leftIR = 14;
int rightIR = 15;
// ultrasonic sensors
int middleEyeTrigger = 8;
int middleEyeEcho = 4;
int leftEyeTrigger = 3;
int leftEyeEcho = 2;
int rightEyeEcho = 12;
int rightEyeTrigger = 13;
int turnTest = 0;

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
  
  // ZBIORY ROZMYTE

  // INPUT
  
  // odleglosc na sensorze srodkowym
  FuzzyInput* distance = new FuzzyInput(1);
  //
  FuzzySet* big = new FuzzySet(30,60,60,60);
  distance->addFuzzySet(big);
  FuzzySet* average = new FuzzySet(0,30,30,60);
  distance->addFuzzySet(average);
  FuzzySet* small = new FuzzySet(0,0,0,30);
  FuzzySet* very_small = new FuzzySet(0,0,0,15);
  distance->addFuzzySet(very_small);
  //
  fuzzy->addFuzzyInput(distance);

  
  // odleglosc na sensorze lewym
  FuzzyInput* distance2 = new FuzzyInput(2);
  //
  FuzzySet* big2 = new FuzzySet(30,60,60,60);
  distance2->addFuzzySet(big2);
  FuzzySet* average2 = new FuzzySet(0,30,30,60);
  distance2->addFuzzySet(average2);
  FuzzySet* small2 = new FuzzySet(0,0,0,30);
  distance2->addFuzzySet(small2);
  FuzzySet* very_small2 = new FuzzySet(0,0,0,15);
  distance2->addFuzzySet(very_small2);
  //
  fuzzy->addFuzzyInput(distance2);

  // odleglosc na sensorze prawym
  FuzzyInput* distance3 = new FuzzyInput(3);
  //
  FuzzySet* big3 = new FuzzySet(30,60,60,60);
  distance3->addFuzzySet(big3);
  FuzzySet* average3 = new FuzzySet(0,30,30,60);
  distance3->addFuzzySet(average3);
  FuzzySet* small3 = new FuzzySet(0,0,0,30);
  distance3->addFuzzySet(small3);
  FuzzySet* very_small3 = new FuzzySet(0,0,0,15);
  distance3->addFuzzySet(very_small3);
  //
  fuzzy->addFuzzyInput(distance3);

  // OUTPUT
  
  // predkosc
  FuzzyOutput* speed = new FuzzyOutput(1);
  //
  FuzzySet* slow = new FuzzySet(0,150,150,150);
  speed->addFuzzySet(slow);
  //
  FuzzySet* mild = new FuzzySet(0,150,150,255);
  speed->addFuzzySet(mild);
  //
  FuzzySet* fast = new FuzzySet(150,255,255,255);
  speed->addFuzzySet(fast);
  //
  fuzzy->addFuzzyOutput(speed);

  //

  // obrot (jak duzy powinien byc, tj. jego czas trwania)
  FuzzyOutput* turn = new FuzzyOutput(2);
  //
  FuzzySet* small_turn = new FuzzySet(300,300,300,600);
  turn->addFuzzySet(small_turn);
  //
  FuzzySet* mild_turn = new FuzzySet(300,600,600,900);
  turn->addFuzzySet(mild_turn);
  //
  FuzzySet* fast_turn = new FuzzySet(600,900,900,900);
  turn->addFuzzySet(fast_turn);
  //
  fuzzy->addFuzzyOutput(turn);

  // kierunek (lewo lub prawo)
  FuzzyOutput* side = new FuzzyOutput(3);
  //
  FuzzySet* left = new FuzzySet(0,0,0,5);
  side->addFuzzySet(left);
  //
  FuzzySet* right = new FuzzySet(5,10,10,10);
  side->addFuzzySet(right);
  //
  fuzzy->addFuzzyOutput(side);


  // ZASADY LOGIKI ROZMYTEJ

  // Pierwsza zasada (jesli Lewo i Prawo Duze, Jedz do przodu szybko)
  FuzzyRuleAntecedent* ifLeftAndRightBig = new FuzzyRuleAntecedent();
  ifLeftAndRightBig->joinWithAND(big2,big3);

  FuzzyRuleAntecedent* ifLeftAndForwardAndRightBig = new FuzzyRuleAntecedent();
  ifLeftAndForwardAndRightBig->joinWithAND(ifLeftAndRightBig,big);

  FuzzyRuleConsequent* GoForwardFast = new FuzzyRuleConsequent();
  GoForwardFast->addOutput(fast);

  FuzzyRule* fuzzyRule01 = new FuzzyRule(1,ifLeftAndForwardAndRightBig,GoForwardFast);
  fuzzy->addFuzzyRule(fuzzyRule01); 


  // Druga zasada (jeśli przód bardzo mały i prawo mały a lewo średnio lub dużo


  FuzzyRuleAntecedent* ifLeftAverageOrBig = new FuzzyRuleAntecedent();
  ifLeftAverageOrBig->joinWithOR(average2,big2);

  FuzzyRuleConsequent* DoALeftSmallTurn = new FuzzyRuleConsequent();
  DoALeftSmallTurn->addOutput(small_turn);
  DoALeftSmallTurn->addOutput(left);

  FuzzyRuleConsequent* DoARightSmallTurn = new FuzzyRuleConsequent();
  DoARightSmallTurn->addOutput(small_turn);
  DoARightSmallTurn->addOutput(right);

  



  // Trzecia zasada (jeśli przód bardzo mało i lewo mały a prawo średnio lub dużo)

  FuzzyRuleAntecedent* ifRightAverageOrBig = new FuzzyRuleAntecedent();
  ifRightAverageOrBig->joinWithOR(average3,big3);


 



  // Zasada jezdzenia 
  
  FuzzyRuleAntecedent* ifLeftAverageOrBigAndRightAverageOrBig = new FuzzyRuleAntecedent();
  ifLeftAverageOrBigAndRightAverageOrBig->joinWithAND(ifLeftAverageOrBig,ifRightAverageOrBig);
    
  FuzzyRuleAntecedent* ifLeftAverageOrBigAndRightAverageOrBigAndForwardAverage = new FuzzyRuleAntecedent();
  ifLeftAverageOrBigAndRightAverageOrBigAndForwardAverage->joinWithAND(ifLeftAverageOrBigAndRightAverageOrBig,average);

  FuzzyRuleConsequent* GoForwardMild = new FuzzyRuleConsequent();
  GoForwardMild->addOutput(slow);

  FuzzyRule* fuzzyRule04 = new FuzzyRule(4,ifLeftAverageOrBigAndRightAverageOrBigAndForwardAverage,GoForwardMild);
  fuzzy->addFuzzyRule(fuzzyRule04); 

  // Kiedy żaden kierunek nie jest dobry

  

  FuzzyRuleAntecedent* ifLeftSmallAndRightSmall = new FuzzyRuleAntecedent();
  ifLeftSmallAndRightSmall->joinWithAND(small2,small3);

  FuzzyRuleAntecedent* ifLeftSmallAndRightSmallAndForwardVerySmall = new FuzzyRuleAntecedent();
  ifLeftSmallAndRightSmallAndForwardVerySmall->joinWithAND(ifLeftSmallAndRightSmall,small);

  FuzzyRuleConsequent* DoALeftMildTurn = new FuzzyRuleConsequent();
  DoALeftMildTurn->addOutput(mild_turn);
  DoALeftMildTurn->addOutput(left);

  FuzzyRule* fuzzyRule05 = new FuzzyRule(5,ifLeftSmallAndRightSmallAndForwardVerySmall,DoALeftMildTurn);
  fuzzy->addFuzzyRule(fuzzyRule05); 

  //
  FuzzyRuleAntecedent* ifLeftAverageAndRightAverage = new FuzzyRuleAntecedent();
  ifLeftAverageAndRightAverage->joinWithAND(average2,average3);
  
  FuzzyRuleAntecedent* ifLeftAverageAndRightAverageAndForwardBig = new FuzzyRuleAntecedent();
  ifLeftAverageAndRightAverageAndForwardBig->joinWithAND(ifLeftAverageAndRightAverage,big);
  
  FuzzyRuleConsequent* GoForwardMild2 = new FuzzyRuleConsequent();
  GoForwardMild2->addOutput(mild);

  FuzzyRule* fuzzyRule06 = new FuzzyRule(6,ifLeftAverageAndRightAverageAndForwardBig,GoForwardMild2);
  fuzzy->addFuzzyRule(fuzzyRule06); 

  FuzzyRuleAntecedent* ifLeftAverageOrBigAndRightAverageOrBigAndForwardVerySmall = new FuzzyRuleAntecedent();
  ifLeftAverageOrBigAndRightAverageOrBigAndForwardVerySmall->joinWithAND(ifLeftAverageOrBigAndRightAverageOrBig,very_small);


  FuzzyRule* fuzzyRule07 = new FuzzyRule(7,ifLeftAverageOrBigAndRightAverageOrBigAndForwardVerySmall,DoARightSmallTurn);
  fuzzy->addFuzzyRule(fuzzyRule07);
  

  //

  //
  FuzzyRuleAntecedent* ifLeftAverageOrRightAverage = new FuzzyRuleAntecedent();
  ifLeftAverageOrRightAverage->joinWithOR(average2,average3);

  FuzzyRuleAntecedent* ifLeftAverageOrRightAverageAndForwardBig = new FuzzyRuleAntecedent();
  ifLeftAverageOrRightAverageAndForwardBig->joinWithAND(ifLeftAverageOrRightAverage,big);
   

  FuzzyRule* fuzzyRule08 = new FuzzyRule(8,ifLeftAverageOrRightAverageAndForwardBig,GoForwardMild2);
  fuzzy->addFuzzyRule(fuzzyRule08);
  

  //
  
  FuzzyRuleAntecedent* ifRightVerySmall = new FuzzyRuleAntecedent();
  ifRightVerySmall->joinSingle(very_small3);

  FuzzyRule* fuzzyRule03 = new FuzzyRule(3,ifRightVerySmall,DoALeftSmallTurn);
  fuzzy->addFuzzyRule(fuzzyRule03); 
  
  FuzzyRuleAntecedent* ifLeftVerySmall = new FuzzyRuleAntecedent();
  ifLeftVerySmall->joinSingle(very_small2);

  FuzzyRule* fuzzyRule02 = new FuzzyRule(2,ifLeftVerySmall,DoARightSmallTurn);
  fuzzy->addFuzzyRule(fuzzyRule02); 

 

   

  
  
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
      motorsForward(0, 140);
      if (btx == 'O') {
        break;
      }
    }
    while (bt_signal == 'B') {
      // drive backward
      btx = (BT.read());
      motorsBackward(0, 140);
      if (btx == 'O') {
        break;
      }
    }
    while (bt_signal == 'L') {
      // turn left
      btx = (BT.read());
      motorsTurnLeft(0, 140);
      if (btx == 'O') {
        break;
      }
    } 
    while (bt_signal == 'R') {
      // turn right
      btx = (BT.read());
      motorsTurnRight(0, 140);
      if (btx == 'O') {
        break;
      }
    }
    while (bt_signal == 'A') {
      // line-tracking
      btx = (BT.read());
      line_tracking();
      if (btx == 'O') {
        break;
      }
    }
    if (bt_signal == 'S') {
      // ultrasonic sensors
    }
  }
}


void loop() {




  

  ultrasonic_sensors();

  
 

  /*
  motorsForward(500,70);
  delay(500);
  motorsForward(500,75);
  delay(500);
  motorsForward(500,80);
  delay(500);
  motorsForward(500,85);
  delay(500);
  */
  
  
  }
  



