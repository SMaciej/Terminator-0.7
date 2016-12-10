// ULTRASONIC SENSORS FUNCTIONS AND ALGORITHMS

void ultrasonic_sensors() {
  
  fuzzy->setInput(1, middleEye.ping_cm()); // middle
  fuzzy->setInput(2, leftEye.ping_cm()); // left
  fuzzy->fuzzify();
  
  int output = 0;
  output = fuzzy->defuzzify(1);
  int output2 = 0;
  output2 = fuzzy->defuzzify(2);
  
  if(output2 == 0 )
  {
    Serial.println(middleEye.ping_cm());
    Serial.println(leftEye.ping_cm());
    Serial.println(output);
    Serial.println("Wykonalem jazde do przodu o mocy ");
    Serial.print(output);
    motorsForward(100,output);
  }
  else
  {
    Serial.println(middleEye.ping_cm());
    Serial.println(leftEye.ping_cm());
    Serial.println(output2);
    Serial.println("wykonalem skret w lewo");
    motorsTurnLeft(output2,125);
  }
  
}






