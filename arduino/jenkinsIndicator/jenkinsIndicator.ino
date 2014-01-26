/*
  Complete code of the Jenkins Build Indicator
  It uses leds to  display the current status of the build of your server, 
  a special LED to highlight when something compiles, and a buzzer to 
  play sounds when an event happens.    
 */
 
// Led that will blink whenever one of the Job is being compiled
int ledBuild = 13;
// Leds of the first Job to be verified
int ledRed1 = 11;  
int ledGreen1 = 12;
// Leds of the second Job to be verified
int ledGreen2 = 10;
int ledRed2 = 9;  

// pin number that triggers the buzzer
int buzzer = 8;

//Whether Jenkins is currently building or not
boolean build = false;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(ledGreen1, OUTPUT);     
  pinMode(ledBuild, OUTPUT);   
  pinMode(ledRed1, OUTPUT);
  pinMode(ledGreen2, OUTPUT);  
  pinMode(ledRed2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  // Sets up the serial connexion to receive info from Jenkins
  Serial.begin(9600);
  Serial.write("READY");
}

/*
* Resets all the indicators
*/
void resetAll() {
  digitalWrite(ledGreen1, LOW);
  digitalWrite(ledBuild, LOW);
  digitalWrite(ledRed1, LOW); 
  digitalWrite(ledGreen2, LOW);
  digitalWrite(ledRed2, LOW);
}

/*
* Resets all the leds for a given project
*/
void reset(char project){
  digitalWrite(ledBuild, LOW);
  if(project == '1'){
    digitalWrite(ledGreen1, LOW);
    digitalWrite(ledRed1, LOW);
  }
  else{
    digitalWrite(ledGreen2, LOW);
    digitalWrite(ledRed2, LOW);
  }
}
  
/*
* Method triggered when one of the Jobs fails
*/
void setFail(char project) {
  if (project == '1'){
    digitalWrite(ledRed1, HIGH);
  } 
  else {
    digitalWrite(ledRed2, HIGH);  
  }
  build = false;
}

/*
* Method triggered when one of the Jobs is successful
*/
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

/*
* Makes the build status LED blink
*/
void blinkBuild(){
  delay(200);     
  digitalWrite(ledBuild, HIGH);   
  delay(200);     
  digitalWrite(ledBuild, LOW);   
  
}

void switchLight(char incomingChar, char project) {
  reset(project);
  
  if (incomingChar == 's') {
    setSuccess(project);
  } 
  else if (incomingChar == 'b') {
    setBuild();
  } 
  else if (incomingChar == 'f') {
    setFail(project);
  } 
  else if (incomingChar == 'o') {
    return;
  }
  
  delay(500);
}

///////////////////////
// BUZZER RELATED CODE/
///////////////////////
/*
* The melody to be played when one of the project fails
*/
void playFail(){
  char notes[] = "cdefgabC";
  int beats[]={2, 2, 2, 2, 2, 2, 2};
  int tempo = 200;
  int length = 8;
  
  for(int i = 0; i < length; i++){
    playNote(notes[i], beats[i] * tempo);
  }
  
}

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(buzzer, HIGH);
    delayMicroseconds(tone);
    digitalWrite(buzzer, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
  
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}
///////////////////////
// MAIN LOOP
///////////////////////
void loop() {
  playFail();
}
//void loop() {
//  if(build == 1){
//    blinkBuild();
//  }
//  
//  if (Serial.available() > 1) {
//    char project = Serial.read();
//    char state = Serial.read();
//    
//    //switchLight('b','1');
//    switchLight(state, project);
//  }  
//}
