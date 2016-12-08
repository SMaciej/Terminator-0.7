// ULTRASONIC SENSORS FUNCTIONS AND ALGORITHMS


unsigned long ping(int ultraSoundSignal) {
  // get sensor value in cm
  
  unsigned long echo = 0;
  unsigned long ultrasoundValue = 0;
  
  pinMode(ultraSoundSignal, OUTPUT); // switch signalpin to output
  digitalWrite(ultraSoundSignal, LOW); // send low pulse
  delayMicroseconds(2); // wait for 2 microseconds
  digitalWrite(ultraSoundSignal, HIGH); // send high pulse
  delayMicroseconds(5); // wait for 5 microseconds
  digitalWrite(ultraSoundSignal, LOW); // holdoff
  pinMode(ultraSoundSignal, INPUT); // switch signalpin to input
  digitalWrite(ultraSoundSignal, HIGH); // turn on pullup resistor
  
  echo = pulseIn(ultraSoundSignal, HIGH); // listen for echo
  ultrasoundValue = (echo / 58.138); // convert to CM then to inches
  
  return ultrasoundValue;
}


int sonic_left() {
   int value = 0;
   int new_value = 0;

   // get maximum
   for (int i=0; i<3; i++) {
     new_value = ping(leftEye);
     if (new_value >= value) {
       value = new_value;
     }
   }

   if(value>=30) {
     value = 30;
   }
   return value;
}


int sonic_middle() {
   int value = 0;
   int new_value = 0;

   // get maximum
   for (int i=0; i<3; i++) {
    new_value = ping(middleEye);
    if (new_value >= value) {
      value = new_value;
    }
   }
   
   if(value>=30) {
    value = 30;
   }
   return value;
}


int sonic_left2() {
   int value = 0;
   int new_value = 0;

   value = ping(leftEye);

   if(value>=30) {
    value = 30;
   }
   if (value == 0)
   {
    return sonic_left2();
   }
   else
   {
   return value;
   }
}


int sonic_middle2() {
   int value = 0;
   int new_value = 0;

   value = ping(middleEye);

   if(value>=30) {
    value = 30;
   }
   if (value == 0)
   {
    return sonic_middle2();
   }
   else
   {
   return value;
   }
} 
  
void ultrasonic_sensors() {
  
  fuzzy->setInput(1, sonic_middle2()); // middle
  fuzzy->setInput(2, sonic_left2()); // left
  fuzzy->fuzzify();

  Serial.println(sonic_middle2());
  Serial.println(sonic_left2());
  
  int output = 0;
  output = fuzzy->defuzzify(1);
  int output2 = 0;
  output2 = fuzzy->defuzzify(2);

  
  
  Serial.println(output);
  Serial.println(output2);
  //output = 125;
  //motorsForward(300,output);
  
  if(output2 == 0 )
  {
  //  Serial.println(sonic_middle());
  //  Serial.println(sonic_left());
  //  Serial.println(output);
    //output = 125;
    motorsForward(300,output);
    Serial.println("Wykonalem jazde do przodu o mocy");
    Serial.println(output);
  }
  else
  {
  //  Serial.println(sonic_middle());
   // Serial.println(sonic_left());
 //   Serial.println(output2);

    Serial.println("wykonalem skret w lewo");
    motorsTurnLeft(output2,125);
   
    
  }
  
}






