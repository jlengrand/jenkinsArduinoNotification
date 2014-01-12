/*
  Traffic Light
  Turns on an LED on if its get an byte input from serial device
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int ledGreen = 12;
int ledBuild = 13;
int ledRed = 11;

boolean build = false;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(ledGreen, OUTPUT);     
  pinMode(ledBuild, OUTPUT);   
  pinMode(ledRed, OUTPUT);   
  Serial.begin(9600);
  Serial.write("READY");
}

void reset() {
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledBuild, LOW);
  digitalWrite(ledRed, LOW); 
}
  
void setFail() {
  digitalWrite(ledRed, HIGH);   
  build = false;
}

void setSuccess() {
  digitalWrite(ledGreen, HIGH);   
  build = false;
}

void setBuild() {
  //digitalWrite(ledBuild, HIGH);   
  build = true;
}

void blinkBuild(){
  delay(200);     
  digitalWrite(ledBuild, HIGH);   
  delay(200);     
  digitalWrite(ledBuild, LOW);   
  
}

void switchLight(char incomingChar) {
  reset();
  
  if (incomingChar == 's') {
    setSuccess();
  } else if (incomingChar == 'b') {
    setBuild();
  } else if (incomingChar == 'f') {
    setFail();
  } else if (incomingChar == 'o') {
    return;
  }
  
  delay(500);
}

// the loop routine runs over and over again forever:
void loop() {
  if(build == 1){
    blinkBuild();
  }
  
  if (Serial.available() > 0) {
    char incomingChar = Serial.read();
    switchLight(incomingChar);
  }  
}
