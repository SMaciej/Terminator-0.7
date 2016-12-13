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
   if ( value > 30)
  {
    value = 30;
  }
   if ( value == 0)
  {
    value = 30;  
  }
  return value;
}

void ultrasonic_sensors() {
Serial.println("oryginalny print");
//Serial.println(middleEye.ping_cm());
  //  Serial.println(limit(leftEye.ping_cm()));

  Serial.println(limit(middleEye.ping_cm(),1));
 // Serial.println(limit(leftEye.ping_cm(),2));
 // Serial.println(limit(rightEye.ping_cm(),3));

  fuzzy->setInput(1, limit(middleEye.ping_cm(),1)); // middle
 // fuzzy->setInput(2, limit(leftEye.ping_cm(),2)); // left
 // fuzzy->setInput(3, limit(rightEye.ping_cm(),3)); // right
  fuzzy->fuzzify();

  

  int output = fuzzy->defuzzify(1);
  int output2 = fuzzy->defuzzify(2);

  Serial.println(output);
  Serial.println(output2);
  
  if(output2 == 0 )
  {
    
    Serial.println("Wykonalem jazde do przodu o mocy ");
    //Serial.print(output);
    motorsForward(100,output);
  }
  else
  {
    //Serial.println(output2);
    Serial.println("wykonalem skret w lewo");
    motorsTurnLeft(output2,125);
  }
  
  //delay(2000);
  
}






