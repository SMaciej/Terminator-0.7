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

  bool wasTheRulleFired = fuzzy->isFiredRule(2);
  Serial.println(wasTheRulleFired);
  
  
  int output = fuzzy->defuzzify(1);
  int output2 = fuzzy->defuzzify(2);
  int output3 = fuzzy->defuzzify(3);


  //Serial.println(output2);
  Serial.println("Output3");
  Serial.println(output);
  Serial.println(output3);

  if ( output3 >= 5)
  {
    Serial.println("Lewo o mocy:");
    Serial.println(output2);
    motorsTurnRight(output2,125);
  }
  else
  {
    if( output3 > 0)
    {
      Serial.println("Prawo o mocy:");
      Serial.println(output2);
      motorsTurnLeft(output2,125);
    }
    else
    {
      motorsForward(50,output);
    }
  }

  
  /*
  Serial.println(output);
  if (output2 >= 1000)
  {
    output2 = output2 - 900;
    Serial.println("Skrecilem w lewo!");
  }
  else
  { 
    if (output2 > 0)
    {
      Serial.println("Skrecilem w prawo!");
    }
  }
  */
  /*
  if (output2 >= 1000)
  {
    Serial.println("lewo");
    output2 = output2 - 750;
  }
  else
  {
    if (output2 > 0)
    {
      Serial.println("prawo");
      output2 = output2 - 450;
    }
  }
  Serial.println(output2);
  */
  /*
  if(output2 == 0 )
  {
    
    Serial.println("Wykonalem jazde do przodu o mocy ");
    //Serial.print(output);
    if(output > 170)
    {
      motorsForward(75,output);
    }
    else
    {
      motorsForward(50,output);
    }
  }
  else
  {
    //Serial.println(output2);
    Serial.println("wykonalem skret w lewo");
    motorsTurnLeft(output2,125);
  }
  */
  //delay(1000);
  
}





