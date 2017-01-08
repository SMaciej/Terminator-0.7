// ULTRASONIC SENSORS FUNCTIONS AND ALGORITHMS

void fuzzy_rules() 
{
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

void ultrasonic_sensors() 
{
  Serial.println("oryginalny print");
  
  Serial.println(limit(leftEye.ping_cm(),2));
  Serial.println(limit(middleEye.ping_cm(),1));
  Serial.println(limit(rightEye.ping_cm(),3));

  fuzzy->setInput(1, limit(middleEye.ping_cm(),1)); // middle
  fuzzy->setInput(2, limit(leftEye.ping_cm(),2)); // left
  fuzzy->setInput(3, limit(rightEye.ping_cm(),3)); // right
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
  wasTheRulleFired = fuzzy->isFiredRule(7);
  Serial.println(wasTheRulleFired);
  wasTheRulleFired = fuzzy->isFiredRule(8);
  Serial.println(wasTheRulleFired);
  wasTheRulleFired = fuzzy->isFiredRule(9);
  Serial.println(wasTheRulleFired);
  
  int output = fuzzy->defuzzify(1);
  int output2 = fuzzy->defuzzify(2);
  int output3 = fuzzy->defuzzify(3);
  int output4 = fuzzy->defuzzify(4);

  //Serial.println(output2);
  Serial.println("Deffuzify");
  Serial.println(output);
  Serial.println(output3);
  Serial.println(output4);

  if ( output3 >= 5 && output4 == 0)
  {
    Serial.println("Prawo o mocy:");
    Serial.println(output2);
    motorsTurnRight(output2,125);
    if(left == 1)
          {
            if(right == 0)
            {
              right++;
              left = 2;
            }
          }
  }
  else
  {
    if( output3 > 0 && output4 == 0)
    {
      Serial.println("Lewo o mocy:");
      Serial.println(output2);
      motorsTurnLeft(output2,125);
      if(left == 0)
          {
            left++;  
          }
          if(left == 2)
          {
            motorsBackward(225,125);
            left = 0;
            right = 0;
            if( limit(leftEye.ping_cm(),2) >= limit(rightEye.ping_cm(),3))
            {
              motorsTurnLeft(700,125);
            }
            else
            {
              motorsTurnRight(700,125);
            }
          }
    }
    else
    {
      if( output4 >0 )
      {
        if( limit(leftEye.ping_cm(),2) >= limit(rightEye.ping_cm(),3))
        {
          motorsTurnLeft(output2,125);
          Serial.println("Inne: Lewo o mocy:");
          Serial.println(output2);
          
          if(left == 0)
          {
            left++;  
          }
          if(left == 2)
          {
            motorsBackward(225,125);
            left == 0;
            right == 0;
            if( limit(leftEye.ping_cm(),2) >= limit(rightEye.ping_cm(),3))
            {
              motorsTurnLeft(700,125);
            }
            else
            {
              motorsTurnRight(700,125);
            }
          }
          
        }
        else
        {
          motorsTurnRight(output2,125);
          Serial.println("Inne :Prawo o mocy:");
          Serial.println(output2);
          if(left == 1)
          {
            if(right == 0)
            {
              right++;
              left == 2;
            }
          }
          
          
        }
      }
      else
      {
        if(output > 170)
        {
          motorsForward(60,output);  
          left = 0;
          right = 0;
        }
        else
        {
          motorsForward(40,output);
          left = 0;
          right = 0;
        }
      }
    }
  }
  //Serial.println(output2);
  Serial.println(left);
  Serial.println(right);
  //delay(1000);
  
}





