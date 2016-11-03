int led = 13;

void setup() {                
  pinMode(led, OUTPUT);     
}

void blink(int length) {
  // blink LED
  digitalWrite(led, HIGH);
  delay(length);
  digitalWrite(led, LOW);
  delay(1000);            
  
}

void loop() {
  blink(3000);
}
