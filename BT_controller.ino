<SoftwareSerial.h>
SoftwareSerial BT(1, 0); 
// creates a "virtual" serial port/UART
// connect BT module TX to D10
// connect BT module RX to D11
// connect BT Vcc to 5V, GND to GND
void setup() 
{
// set digital pin to control as an output
pinMode(13, OUTPUT);
// set the data rate for the SoftwareSerial port
BT.begin(9600);
// Send test message to other device
BT.println("Hello from Arduino");
}
String a; // stores incoming character from other device
void loop() 
{
if (BT.available())
// if text arrived in from BT serial...
{
a=(String)(BT.read());
if (a=='TF')
{
digitalWrite(13, HIGH);
BT.println("LED on");
}
if (a=='TO')
{
digitalWrite(13, LOW);
BT.println("LED off");
}
if (a=='?')
{
BT.println("Send '1' to turn LED on");
BT.println("Send '2' to turn LED on");
} 
// you can add more "if" statements with other characters to add more commands
}
}
