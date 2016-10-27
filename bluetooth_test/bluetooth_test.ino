int led = 12;

void setup() {                
  pinMode(led, OUTPUT);     
}

void blink {
  // blink LED
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);            
  
}

void loop() {

}
