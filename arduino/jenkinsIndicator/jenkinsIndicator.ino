/*
  Traffic Light
  Turns on an LED on if its get an byte input from serial device
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int ledGreen1 = 12;
int ledBuild = 13;
int ledRed1 = 11;
int ledGreen2 = 10;
int ledRed2 = 9;
//int project = 0;


boolean build = false;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(ledGreen1, OUTPUT);     
  pinMode(ledBuild, OUTPUT);   
  pinMode(ledRed1, OUTPUT);
  pinMode(ledGreen2, OUTPUT);  
  pinMode(ledRed2, OUTPUT);
  Serial.begin(9600);
  Serial.write("READY");
}

void reset() {
  digitalWrite(ledGreen1, LOW);
  digitalWrite(ledBuild, LOW);
  digitalWrite(ledRed1, LOW); 
  digitalWrite(ledGreen2, LOW);
  digitalWrite(ledRed2, LOW);
}
  
void setFail(char project) {
  if (project == '1'){
    digitalWrite(ledRed1, HIGH);
  } 
  else {
    digitalWrite(ledRed2, HIGH);  
  }
  build = false;
}

void setSuccess(char project) {
  if (project == '1'){
    digitalWrite(ledGreen1, HIGH);
  }
  else {
    digitalWrite(ledGreen2, HIGH);   
  }
  build = false;
}

void setBuild() {   
  build = true;
}

void blinkBuild(){
  delay(200);     
  digitalWrite(ledBuild, HIGH);   
  delay(200);     
  digitalWrite(ledBuild, LOW);   
  
}

void switchLight(char incomingChar, char project) {
  reset();
  
  if (incomingChar == 's') {
    setSuccess(project);
  } else if (incomingChar == 'b') {
    setBuild();
  } else if (incomingChar == 'f') {
    setFail(project);
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
  
  if (Serial.available() > 1) {
    char project = Serial.read();
    char state = Serial.read();
    
    //switchLight('b','1');
    switchLight(state, project);
  }  
}
