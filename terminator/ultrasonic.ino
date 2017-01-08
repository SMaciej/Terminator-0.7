// ULTRASONIC SENSORS FUNCTIONS AND ALGORITHMS


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

void ultrasonic_sensors() {
Serial.println("oryginalny print");
//Serial.println(middleEye.ping_cm());
  //  Serial.println(limit(leftEye.ping_cm()));

  
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





