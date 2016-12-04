#include <Fuzzy.h>
#include <FuzzyComposition.h>
#include <FuzzyInput.h>
#include <FuzzyIO.h>
#include <FuzzyOutput.h>
#include <FuzzyRule.h>
#include <FuzzyRuleAntecedent.h>
#include <FuzzyRuleConsequent.h>
#include <FuzzySet.h>

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
Fuzzy* fuzzy = new Fuzzy();


void setup() {
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  // set serial
  Serial.begin(9600);

  int distance = 15;


  FuzzyInput* sensor = new FuzzyInput(1);

  FuzzySet* safe = new FuzzySet(15,30,30,30);
  sensor->addFuzzySet(safe);
  FuzzySet* duno = new FuzzySet(0,15,15,30);
  sensor->addFuzzySet(duno);
  FuzzySet* dang = new FuzzySet(0,0,0,15);
  sensor->addFuzzySet(dang);

  fuzzy->addFuzzyInput(sensor);
  

  FuzzyOutput* speed = new FuzzyOutput(1);

  FuzzySet* slow = new FuzzySet(70,120,120,120);
  speed->addFuzzySet(slow);
  FuzzySet* mild = new FuzzySet(100,125,125,150);
  speed->addFuzzySet(mild);
  FuzzySet* fast = new FuzzySet(125,230,230,230);
  speed->addFuzzySet(fast);

  fuzzy->addFuzzyOutput(speed);

  // Zasady logiki rozmytej
  // Zasada pierwsza
  FuzzyRuleAntecedent* ifSensorSafe = new FuzzyRuleAntecedent();
  ifSensorSafe->joinSingle(safe);
  FuzzyRuleConsequent* thenSpeedFast = new FuzzyRuleConsequent();
  thenSpeedFast->addOutput(fast);
  
  FuzzyRule* fuzzyRule01 = new FuzzyRule(1, ifSensorSafe, thenSpeedFast);
  fuzzy->addFuzzyRule(fuzzyRule01);

  // Zasada Druga
  FuzzyRuleAntecedent* ifSensorDuno = new FuzzyRuleAntecedent();
  ifSensorDuno->joinSingle(duno);
  FuzzyRuleConsequent* thenSpeedMild = new FuzzyRuleConsequent();
  thenSpeedMild->addOutput(mild);

  FuzzyRule* fuzzyRule02 = new FuzzyRule(1, ifSensorDuno, thenSpeedMild);
  fuzzy->addFuzzyRule(fuzzyRule02);

  // Zasada Trzecia
  FuzzyRuleAntecedent* ifSensorDang = new FuzzyRuleAntecedent();
  ifSensorDang->joinSingle(dang);
  FuzzyRuleConsequent* thenSpeedSlow = new FuzzyRuleConsequent();
  thenSpeedSlow->addOutput(slow);

  FuzzyRule* fuzzyRule03 = new FuzzyRule(1, ifSensorDang, thenSpeedSlow);
  fuzzy->addFuzzyRule(fuzzyRule03);
  


  


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

int calc(int distance) {

  distance = distance + 5;
}
int distance = 15;

void loop() {
   delay(3000);
  //motorsOff();
  //delay(3000);
  //motorsForward(2000,100);
  //motorsTurnLeft(700,140);
  //motorsForward(2000,100);
  //motorsTurnLeft(700,140); 
  //motorsForward(1000,250);
  //motorsBackward(1000,250); 
  //Serial.println(IRleft()); // print the data from the left sensor
  int result = IRleft() + IRright();
  distance = random(0,30);
 
 

  Serial.println(distance);

  fuzzy->setInput(1, distance);
  fuzzy->fuzzify();

  float output = fuzzy->defuzzify(1);

  Serial.println(output);
  
  motorsForward(100,output);

 


  
 /* 
  if(IRleft() == 1 && IRright() == 1)
  {
    motorsForward(10,85);
  }
  if(IRleft() == 0 && IRright() == 1)
  {
    motorsTurnRight(10,110);
  }
  if(IRright() == 0 && IRleft() == 1)
  {
    motorsTurnLeft(10,110);
  }
  */
  
  
 // motorsForward(10,100);
   
}
