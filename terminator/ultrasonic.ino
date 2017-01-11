// ULTRASONIC SENSORS FUNCTIONS AND ALGORITHMS

void fuzzy_rules()
{
  // ZBIORY ROZMYTE

  // INPUT
  
  // odleglosc na sensorze srodkowym
  FuzzyInput* distance = new FuzzyInput(1);
  //
  FuzzySet* big = new FuzzySet(30, 60, 60, 60);
  distance->addFuzzySet(big);
  FuzzySet* average = new FuzzySet(0, 30, 30, 60);
  distance->addFuzzySet(average);
  FuzzySet* small = new FuzzySet(0, 0, 0, 30);
  distance->addFuzzySet(small);
  FuzzySet* very_small = new FuzzySet(0, 0, 0, 15);
  distance->addFuzzySet(very_small);
  //
  fuzzy->addFuzzyInput(distance);


  // odleglosc na sensorze lewym
  FuzzyInput* distance2 = new FuzzyInput(2);
  //
  FuzzySet* big2 = new FuzzySet(30, 60, 60, 60);
  distance2->addFuzzySet(big2);
  FuzzySet* average2 = new FuzzySet(0, 30, 30, 60);
  distance2->addFuzzySet(average2);
  FuzzySet* small2 = new FuzzySet(0, 0, 0, 30);
  distance2->addFuzzySet(small2);
  FuzzySet* very_small2 = new FuzzySet(0, 0, 0, 15);
  distance2->addFuzzySet(very_small2);
  //
  fuzzy->addFuzzyInput(distance2);

  // odleglosc na sensorze prawym
  FuzzyInput* distance3 = new FuzzyInput(3);
  //
  FuzzySet* big3 = new FuzzySet(30, 60, 60, 60);
  distance3->addFuzzySet(big3);
  FuzzySet* average3 = new FuzzySet(0, 30, 30, 60);
  distance3->addFuzzySet(average3);
  FuzzySet* small3 = new FuzzySet(0, 0, 0, 30);
  distance3->addFuzzySet(small3);
  FuzzySet* very_small3 = new FuzzySet(0, 0, 0, 15);
  distance3->addFuzzySet(very_small3);
  //
  fuzzy->addFuzzyInput(distance3);

  // OUTPUT

  // predkosc
  FuzzyOutput* speed = new FuzzyOutput(1);
  //
  FuzzySet* slow = new FuzzySet(0, 150, 150, 150);
  speed->addFuzzySet(slow);
  //
  FuzzySet* mild = new FuzzySet(0, 150, 150, 255);
  speed->addFuzzySet(mild);
  //
  FuzzySet* fast = new FuzzySet(150, 255, 255, 255);
  speed->addFuzzySet(fast);
  //
  fuzzy->addFuzzyOutput(speed);

  // zakręt
  FuzzyOutput* turn = new FuzzyOutput(2);
  //
  FuzzySet* small_turn = new FuzzySet(150, 150, 150, 450);
  turn->addFuzzySet(small_turn);
  //
  FuzzySet* mild_turn = new FuzzySet(150, 450, 450, 900);
  turn->addFuzzySet(mild_turn);
  //
  FuzzySet* fast_turn = new FuzzySet(450, 900, 900, 900);
  turn->addFuzzySet(fast_turn);
  //
  fuzzy->addFuzzyOutput(turn);

  // kierunek (lewo, prawo, nieokreślony)
  FuzzyOutput* side = new FuzzyOutput(3);
  //
  FuzzySet* left = new FuzzySet(0, 0, 0, 5);
  side->addFuzzySet(left);
  //
  FuzzySet* right = new FuzzySet(5, 10, 10, 10);
  side->addFuzzySet(right);
  //
  FuzzySet* unknown = new FuzzySet(10, 15, 15, 15);
  side->addFuzzySet(unknown);
  //
  fuzzy->addFuzzyOutput(side);


  // ZASADY LOGIKI ROZMYTEJ

  // Pierwsza zasada (jesli Lewo i Prawo Duze, Jedz do przodu szybko)
  FuzzyRuleAntecedent* ifLeftAndRightBig = new FuzzyRuleAntecedent();
  ifLeftAndRightBig->joinWithAND(big2, big3);

  FuzzyRuleAntecedent* ifLeftAndForwardAndRightBig = new FuzzyRuleAntecedent();
  ifLeftAndForwardAndRightBig->joinWithAND(ifLeftAndRightBig, big);

  FuzzyRuleConsequent* GoForwardFast = new FuzzyRuleConsequent();
  GoForwardFast->addOutput(fast);

  FuzzyRule* fuzzyRule01 = new FuzzyRule(1, ifLeftAndForwardAndRightBig, GoForwardFast);
  fuzzy->addFuzzyRule(fuzzyRule01);
  /*
  // Druga zasada (jeśli lewo bardzo małe skręć w prawo)
  FuzzyRuleConsequent* DoARightSmallTurn = new FuzzyRuleConsequent();
  DoARightSmallTurn->addOutput(small_turn);
  DoARightSmallTurn->addOutput(right);

  FuzzyRuleAntecedent* ifLeftVerySmall = new FuzzyRuleAntecedent();
  ifLeftVerySmall->joinSingle(very_small2);

  FuzzyRule* fuzzyRule02 = new FuzzyRule(2, ifLeftVerySmall, DoARightSmallTurn);
  fuzzy->addFuzzyRule(fuzzyRule02);

  // Trzecia zasada (jeśli prawo bardzo małe skręć w lewo)
  FuzzyRuleAntecedent* ifRightVerySmall = new FuzzyRuleAntecedent();
  ifRightVerySmall->joinSingle(very_small3);

  FuzzyRuleConsequent* DoALeftSmallTurn = new FuzzyRuleConsequent();
  DoALeftSmallTurn->addOutput(small_turn);
  DoALeftSmallTurn->addOutput(left);

  FuzzyRule* fuzzyRule03 = new FuzzyRule(3, ifRightVerySmall, DoALeftSmallTurn);
  fuzzy->addFuzzyRule(fuzzyRule03);
  */

  
  // Czwarta zasada (main) (jeśli lewo średnie lub duże i prawo średnie lub duże i przód średni jedź z średnią prędkością)
  FuzzyRuleAntecedent* ifLeftAverageOrBig = new FuzzyRuleAntecedent();
  ifLeftAverageOrBig->joinWithOR(average2, big2);

  FuzzyRuleAntecedent* ifRightAverageOrBig = new FuzzyRuleAntecedent();
  ifRightAverageOrBig->joinWithOR(average3, big3);
  
  FuzzyRuleAntecedent* ifLeftAverageOrBigAndRightAverageOrBig = new FuzzyRuleAntecedent();
  ifLeftAverageOrBigAndRightAverageOrBig->joinWithAND(ifLeftAverageOrBig, ifRightAverageOrBig);

  FuzzyRuleAntecedent* ifLeftAverageOrBigAndRightAverageOrBigAndForwardAverage = new FuzzyRuleAntecedent();
  ifLeftAverageOrBigAndRightAverageOrBigAndForwardAverage->joinWithAND(ifLeftAverageOrBigAndRightAverageOrBig, average);

  FuzzyRuleConsequent* GoForwardMild = new FuzzyRuleConsequent();
  GoForwardMild->addOutput(mild);
  
  FuzzyRule* fuzzyRule04 = new FuzzyRule(4, ifLeftAverageOrBigAndRightAverageOrBigAndForwardAverage, GoForwardMild);
  fuzzy->addFuzzyRule(fuzzyRule04);

  // Zasada piąta (jeśli przedni sensor podaje małe odległości)
  FuzzyRuleConsequent* DoAMildTurn = new FuzzyRuleConsequent();
  DoAMildTurn->addOutput(mild_turn);
  DoAMildTurn->addOutput(unknown);
  
  FuzzyRuleAntecedent* ifForwardVerySmall = new FuzzyRuleAntecedent();
  ifForwardVerySmall->joinSingle(very_small);

  FuzzyRule* fuzzyRule05 = new FuzzyRule(5, ifForwardVerySmall, DoAMildTurn);
  fuzzy->addFuzzyRule(fuzzyRule05);

  
  //Zasada szósta (jeśli lewo średnie lub prawo średnie i przód duży, jedź z średnią prędkością)
  FuzzyRuleAntecedent* ifLeftAverageAndRightAverage = new FuzzyRuleAntecedent();
  ifLeftAverageAndRightAverage->joinWithOR(average2, average3);

  FuzzyRuleAntecedent* ifLeftAverageAndRightAverageAndForwardBig = new FuzzyRuleAntecedent();
  ifLeftAverageAndRightAverageAndForwardBig->joinWithAND(ifLeftAverageAndRightAverage, big);

  FuzzyRule* fuzzyRule06 = new FuzzyRule(6, ifLeftAverageAndRightAverageAndForwardBig, GoForwardMild);
  fuzzy->addFuzzyRule(fuzzyRule06);

      // Druga zasada (jeśli lewo bardzo małe skręć w prawo)
  FuzzyRuleConsequent* DoARightSmallTurn = new FuzzyRuleConsequent();
  DoARightSmallTurn->addOutput(small_turn);
  DoARightSmallTurn->addOutput(right);

  FuzzyRuleAntecedent* ifLeftVerySmallAndRightBig = new FuzzyRuleAntecedent();
  ifLeftVerySmallAndRightBig->joinWithAND(very_small2,big3);

  FuzzyRule* fuzzyRule02 = new FuzzyRule(2, ifLeftVerySmallAndRightBig, DoARightSmallTurn);
  fuzzy->addFuzzyRule(fuzzyRule02);

  // Trzecia zasada (jeśli prawo bardzo małe skręć w lewo)
  FuzzyRuleAntecedent* ifRightVerySmallAndLeftBig = new FuzzyRuleAntecedent();
  ifRightVerySmallAndLeftBig->joinWithAND(very_small3,big2);

  FuzzyRuleConsequent* DoALeftSmallTurn = new FuzzyRuleConsequent();
  DoALeftSmallTurn->addOutput(small_turn);
  DoALeftSmallTurn->addOutput(left);

  FuzzyRule* fuzzyRule03 = new FuzzyRule(3, ifRightVerySmallAndLeftBig, DoALeftSmallTurn);
  fuzzy->addFuzzyRule(fuzzyRule03);  

}




void ultrasonic_sensors()
{
  Serial.println("oryginalny print");

  Serial.println(limit(leftEye.ping_cm(), 2));
  Serial.println(limit(middleEye.ping_cm(), 1));
  Serial.println(limit(rightEye.ping_cm(), 3));

  fuzzy->setInput(1, limit(middleEye.ping_cm(), 1)); // middle
  fuzzy->setInput(2, limit(leftEye.ping_cm(), 2)); // left
  fuzzy->setInput(3, limit(rightEye.ping_cm(), 3)); // right
  fuzzy->fuzzify();

  Serial.println("Zasady:");
  bool wasTheRulleFired = fuzzy->isFiredRule(1);
  Serial.println(wasTheRulleFired);
  wasTheRulleFired = fuzzy->isFiredRule(2);
  Serial.println(wasTheRulleFired);
  wasTheRulleFired = fuzzy->isFiredRule(3);
  Serial.println(wasTheRulleFired);
  wasTheRulleFired = fuzzy->isFiredRule(4);
  Serial.println(wasTheRulleFired);
  wasTheRulleFired = fuzzy->isFiredRule(5);
  Serial.println(wasTheRulleFired);
  wasTheRulleFired = fuzzy->isFiredRule(6);
  Serial.println(wasTheRulleFired);

  int output = fuzzy->defuzzify(1);
  int output2 = fuzzy->defuzzify(2);
  int output3 = fuzzy->defuzzify(3);

  //Serial.println(output2);
  Serial.println("Deffuzify");
  Serial.println(output);
  Serial.println(output3);

  if ( output3 >= 5 && output3 < 10)
  {
    Serial.println("Prawo o mocy:");
    Serial.println(output2);
    motorsTurnRight(output2, 125);
    if (left == 1)
    {
      if (right == 0)
      {
        right++;
        left = 2;
      }
    }
    if (right2 == 0)
    {
      left2++;
    }
    if (right2 == 2)
    {
       motorsBackward(225, 125);
       left2 = 0;
       right2 = 0;
       if ( limit(leftEye.ping_cm(), 2) >= limit(rightEye.ping_cm(), 3))
       {
         motorsTurnLeft(800, 125);
       }
       else
       {
         motorsTurnRight(800, 125);
       }
    }
  }
  else
  {
    if ( output3 > 0 && output3 < 10)
    {
      Serial.println("Lewo o mocy:");
      Serial.println(output2);
      motorsTurnLeft(output2, 125);
      if (left == 0)
      {
        left++;
      }
      if (left == 2)
      {
        motorsBackward(225, 125);
        left = 0;
        right = 0;
        if ( limit(leftEye.ping_cm(), 2) >= limit(rightEye.ping_cm(), 3))
        {
          motorsTurnLeft(800, 125);
        }
        else
        {
          motorsTurnRight(800, 125);
        }
      }
      
      if (right2 == 1)
      {
        if (left2 == 0)
        {
          left2++;
          right2 = 2;
        }
      }
      
    }
    else
    {
      if ( output3 > 0 )
      {
        if ( limit(leftEye.ping_cm(), 2) >= limit(rightEye.ping_cm(), 3))
        {
          motorsTurnLeft(output2, 125);
          Serial.println("Inne: Lewo o mocy:");
          Serial.println(output2);

          if (left == 0)
          {
            left++;
          }
          if (left == 2)
          {
            motorsBackward(225, 125);
            left == 0;
            right == 0;
            if ( limit(leftEye.ping_cm(), 2) >= limit(rightEye.ping_cm(), 3))
            {
              motorsTurnLeft(800, 125);
            }
            else
            {
              motorsTurnRight(800, 125);
            }
          }

        }
        else
        {
          motorsTurnRight(output2, 125);
          Serial.println("Inne :Prawo o mocy:");
          Serial.println(output2);
          if (left == 1)
          {
            if (right == 0)
            {
              right++;
              left == 2;
            }
          }


        }
      }
      else
      {
        if (output > 170)
        {
          motorsForward(40, output);
          left = 0;
          right = 0;
          left2 = 0;
          right2 = 0;
        }
        else
        {
          motorsForward(25, output);
          left = 0;
          right = 0;
          left2 = 0;
          right2 = 0;
        }
      }
    }
  }
  //Serial.println(output2);
  Serial.println(left);
  Serial.println(right);
  //delay(1000);

}





