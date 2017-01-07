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
  distance2->addFuzzySet(very_small3);
  //
  fuzzy->addFuzzyInput(distance3);

  // OUTPUT
  
  // predkosc
  FuzzyOutput* speed = new FuzzyOutput(1);
  //

  FuzzySet* slow = new FuzzySet(0,150,150,150);
  speed->addFuzzySet(slow);

  FuzzySet* mild = new FuzzySet(0,150,150,255);
  speed->addFuzzySet(mild);

  FuzzySet* fast = new FuzzySet(150,255,255,255);
  speed->addFuzzySet(fast);
  //
  fuzzy->addFuzzyOutput(speed);

  // to psuje! 
  /*
  // predkosc lewego skretu
  FuzzyOutput* speed2 = new FuzzyOutput(2);
  //
  FuzzySet* slow2 = new FuzzySet(85,120,120,120);
  speed->addFuzzySet(slow2);
  FuzzySet* mild2 = new FuzzySet(100,125,125,150);
  speed->addFuzzySet(mild2);
  FuzzySet* fast2 = new FuzzySet(125,230,230,230);
  speed->addFuzzySet(fast2);
  //
  fuzzy->addFuzzyOutput(speed2);

  // predkosc prawego skretu
  FuzzyOutput* speed3 = new FuzzyOutput(3);
  //
  FuzzySet* slow3 = new FuzzySet(85,120,120,120);
  speed->addFuzzySet(slow3);
  FuzzySet* mild3 = new FuzzySet(100,125,125,150);
  speed->addFuzzySet(mild3);
  FuzzySet* fast3 = new FuzzySet(125,230,230,230);
  speed->addFuzzySet(fast3);
  //
  fuzzy->addFuzzyOutput(speed3);
  */
  //

  // obrot (jak duzy powinien byc, tzn czas trwania)
  FuzzyOutput* turn = new FuzzyOutput(2);
  //
  // Lewy skret 
  /*
  FuzzySet* left_small_turn = new FuzzySet(1200,1500,1500,1500);
  turn->addFuzzySet(left_small_turn);
  FuzzySet* left_mild_turn = new FuzzySet(1200,1500,1500,1800);
  turn->addFuzzySet(left_mild_turn);
  FuzzySet* left_fast_turn = new FuzzySet(1500,1800,1800,1800);
  turn->addFuzzySet(left_fast_turn);
  // Prawy skret
  FuzzySet* right_small_turn = new FuzzySet(300,600,600,600);
  turn->addFuzzySet(right_small_turn);
  FuzzySet* right_mild_turn = new FuzzySet(300,600,600,900);
  turn->addFuzzySet(right_mild_turn);
  FuzzySet* right_fast_turn = new FuzzySet(600,900,900,1200);
  turn->addFuzzySet(right_fast_turn);
  */

  
  // Prawy skret
  FuzzySet* right_small_turn = new FuzzySet(300,300,300,600);
  turn->addFuzzySet(right_small_turn);
  FuzzySet* right_mild_turn = new FuzzySet(300,600,600,900);
  turn->addFuzzySet(right_mild_turn);
  FuzzySet* right_fast_turn = new FuzzySet(600,900,900,900);
  turn->addFuzzySet(right_fast_turn);
  //
  fuzzy->addFuzzyOutput(turn);

  
  FuzzyOutput* side = new FuzzyOutput(3);
  FuzzySet* left = new FuzzySet(0,0,0,5);
  side->addFuzzySet(left);
  FuzzySet* right = new FuzzySet(5,10,10,10);
  side->addFuzzySet(right);
  //
  fuzzy->addFuzzyOutput(side);

  /*
  FuzzyOutput* turn2 = new FuzzyOutput(3);
  // Lewy skret
  FuzzySet* left_small_turn = new FuzzySet(300,300,300,600);
  turn2->addFuzzySet(left_small_turn);
  FuzzySet* left_mild_turn = new FuzzySet(300,600,600,900);
  turn2->addFuzzySet(left_mild_turn);
  FuzzySet* left_fast_turn = new FuzzySet(600,900,900,900);
  turn2->addFuzzySet(left_fast_turn);
  //
  fuzzy->addFuzzyOutput(turn2);
  */
  
  // ZASADY LOGIKI ROZMYTEJ

  // Pierwsza zasada
  FuzzyRuleAntecedent* ifLeftAndRightBig = new FuzzyRuleAntecedent();
  ifLeftAndRightBig->joinWithAND(big2,big3);

  FuzzyRuleAntecedent* ifLeftAndForwardAndRightBig = new FuzzyRuleAntecedent();
  ifLeftAndForwardAndRightBig->joinWithAND(ifLeftAndRightBig,big);

  FuzzyRuleConsequent* GoForwardFast = new FuzzyRuleConsequent();
  GoForwardFast->addOutput(fast);

  FuzzyRule* fuzzyRule01 = new FuzzyRule(1,ifLeftAndForwardAndRightBig,GoForwardFast);
  fuzzy->addFuzzyRule(fuzzyRule01); 

  
  // Druga zasada
  FuzzyRuleAntecedent* ifLeftBigAndRightSmall = new FuzzyRuleAntecedent();
  ifLeftBigAndRightSmall->joinWithAND(big2,small3);

  FuzzyRuleAntecedent* ForwardVerySmall = new FuzzyRuleAntecedent();
  ForwardVerySmall->joinSingle(very_small);
  
  FuzzyRuleAntecedent* ifLeftBigForwardVerySmallAndRightSmall = new FuzzyRuleAntecedent();
  ifLeftBigForwardVerySmallAndRightSmall->joinWithAND(ifLeftBigAndRightSmall,ForwardVerySmall);

  FuzzyRuleConsequent* DoALeftMildTurn = new FuzzyRuleConsequent();
  DoALeftMildTurn->addOutput(right_mild_turn);
  DoALeftMildTurn->addOutput(left);

  FuzzyRule* fuzzyRule02 = new FuzzyRule(2,ifLeftBigForwardVerySmallAndRightSmall,DoALeftMildTurn);
  fuzzy->addFuzzyRule(fuzzyRule02); 
  
 
  // Trzecia zasada
  FuzzyRuleAntecedent* ifForwardVerySmallAndLeftSmall = new FuzzyRuleAntecedent();
  ifForwardVerySmallAndLeftSmall->joinWithAND(very_small,small2);

  FuzzyRuleAntecedent* IfRightBig = new FuzzyRuleAntecedent();
  IfRightBig->joinSingle(big3);

  FuzzyRuleAntecedent* ifLeftSmallForwardVerySmallAndRightBig = new FuzzyRuleAntecedent();
  ifLeftSmallForwardVerySmallAndRightBig->joinWithAND(ifForwardVerySmallAndLeftSmall,IfRightBig);

  FuzzyRuleConsequent* DoARightMildTurn = new FuzzyRuleConsequent();
  DoARightMildTurn->addOutput(right_mild_turn);
  DoARightMildTurn->addOutput(right);

  FuzzyRule* fuzzyRule03 = new FuzzyRule(3,ifLeftSmallForwardVerySmallAndRightBig,DoARightMildTurn);
  fuzzy->addFuzzyRule(fuzzyRule03); 
  
  /*
  FuzzyRuleAntecedent* ifForwardVerySmall = new FuzzyRuleAntecedent();
  ifForwardVerySmall ->joinSingle(very_small);

  FuzzyRuleConsequent* DoATurn= new FuzzyRuleConsequent();
  DoATurn->addOutput(mild_turn);

  FuzzyRule* fuzzyRule01 = new FuzzyRule(1, ifForwardVerySmall, DoATurn);
  fuzzy->addFuzzyRule(fuzzyRule01);
  //

  FuzzyRuleAntecedent* ifForwardSmall = new FuzzyRuleAntecedent();
  ifForwardSmall ->joinSingle(small);

  FuzzyRuleConsequent* GoForwardSlow= new FuzzyRuleConsequent();
  DoATurn->addOutput(slow);

  FuzzyRule* fuzzyRule04 = new FuzzyRule(1, ifForwardSmall, GoForwardSlow);
  fuzzy->addFuzzyRule(fuzzyRule04);
  
  FuzzyRuleAntecedent* ifForwardAverage= new FuzzyRuleAntecedent();
  ifForwardAverage->joinSingle(average);

  FuzzyRuleConsequent* GoForwardMild= new FuzzyRuleConsequent();
  GoForwardMild->addOutput(mild);

  FuzzyRule* fuzzyRule02 = new FuzzyRule(2, ifForwardAverage, GoForwardMild);
  fuzzy->addFuzzyRule(fuzzyRule02);
  //
  FuzzyRuleAntecedent* ifForwardBig= new FuzzyRuleAntecedent();
  ifForwardBig->joinSingle(big);

  FuzzyRuleConsequent* GoForwardFast= new FuzzyRuleConsequent();
  GoForwardFast->addOutput(fast);

  FuzzyRule* fuzzyRule03 = new FuzzyRule(3, ifForwardBig, GoForwardFast);
  fuzzy->addFuzzyRule(fuzzyRule03);
  


  /*
  FuzzyRuleAntecedent* LeftSmallAndRightSmall = new FuzzyRuleAntecedent();
  LeftSmallAndRightSmall->joinWithAND(small2,small3);

  FuzzyRuleAntecedent* LeftAverageAndRightAverage = new FuzzyRuleAntecedent();
  LeftAverageAndRightAverage->joinWithAND(average2,average3);

  FuzzyRuleAntecedent* LeftBigAndRightBig = new FuzzyRuleAntecedent();
  LeftBigAndRightBig->joinWithAND(big2,big3);

  FuzzyRuleAntecedent* LeftBigAndRightSmall = new FuzzyRuleAntecedent();
  LeftBigAndRightSmall->joinWithAND(big2,small3);

  FuzzyRuleAntecedent* LeftSmallAndRightBig = new FuzzyRuleAntecedent();
  LeftSmallAndRightBig->joinWithAND(small,big3);


  
  // zasada pierwsza | jesli sensory = malo miejsca, skrec w miejscu
  
  FuzzyRuleAntecedent* middleSmallAndLeftSmallAndRightSmall = new FuzzyRuleAntecedent();
  middleSmallAndLeftSmallAndRightSmall->joinWithAND(LeftSmallAndRightSmall,small);
  
  FuzzyRuleConsequent* DoATurn= new FuzzyRuleConsequent();
  DoATurn->addOutput(mild_turn);
  //
  FuzzyRule* fuzzyRule01 = new FuzzyRule(1, middleSmallAndLeftSmallAndRightSmall, DoATurn);
  fuzzy->addFuzzyRule(fuzzyRule01);

  // zasada druga | jesli sensory = srednio miejsca, jedz do przodu z srednia predkoscia
 
  FuzzyRuleAntecedent* middleAverageAndLeftAverageAndRightAverage = new FuzzyRuleAntecedent();
  middleAverageAndLeftAverageAndRightAverage->joinWithAND(LeftAverageAndRightAverage,average);
  
  FuzzyRuleConsequent* ForwardMild= new FuzzyRuleConsequent();
  ForwardMild->addOutput(mild);
  //
  FuzzyRule* fuzzyRule02 = new FuzzyRule(2, middleAverageAndLeftAverageAndRightAverage, ForwardMild);
  fuzzy->addFuzzyRule(fuzzyRule02);

  // zasada  trzecia | jesli sensory = duzo miejsca, jedz do przodu z duza predkoscia
 
  FuzzyRuleAntecedent* middleBigAndLeftBigAndRightBig = new FuzzyRuleAntecedent();
  middleBigAndLeftBigAndRightBig->joinWithAND(LeftBigAndRightBig,big);
  
  FuzzyRuleConsequent* ForwardFast= new FuzzyRuleConsequent();
  ForwardFast->addOutput(fast);
  //
  FuzzyRule* fuzzyRule03 = new FuzzyRule(2, middleBigAndLeftBigAndRightBig, ForwardFast);
  fuzzy->addFuzzyRule(fuzzyRule03);

  // zasada czwarta | jesli sensory = z przodu dużo, lewo i prawo srednio, jedz do przodu z srednia predkoscia
 
  FuzzyRuleAntecedent* middleBigAndLeftAverageAndRightAverage = new FuzzyRuleAntecedent();
  middleBigAndLeftAverageAndRightAverage->joinWithAND(LeftAverageAndRightAverage,big);
  

  FuzzyRule* fuzzyRule04 = new FuzzyRule(2, middleAverageAndLeftAverageAndRightAverage, ForwardMild);
  fuzzy->addFuzzyRule(fuzzyRule02);
  
  ;

  /*
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
  */
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
  



