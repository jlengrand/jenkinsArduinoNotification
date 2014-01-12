/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led_compute = 13;
int led_projet1_ok=12;
int led_projet1_fail=11;
int led_projet2_ok=10;
int led_projet2_fail=9;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led_compute, OUTPUT);
  pinMode(led_projet1_ok, OUTPUT);
  pinMode(led_projet1_fail, OUTPUT);
  pinMode(led_projet2_ok, OUTPUT);
  pinMode(led_projet2_fail, OUTPUT);  
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led_compute, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(led_projet1_ok, HIGH);
  digitalWrite(led_projet1_fail, HIGH);
  digitalWrite(led_projet2_ok, HIGH);
  digitalWrite(led_projet2_fail, HIGH);
  delay(2000);               // wait for a second
  digitalWrite(led_compute, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(led_projet1_ok, LOW);
  digitalWrite(led_projet1_fail, LOW);
  digitalWrite(led_projet2_ok, LOW);
  digitalWrite(led_projet2_fail, LOW);
  delay(2000);               // wait for a second
}
