#define fsrOne 3
#define fsrTwo 4
#define fsrThree 5
#define fsrFour 6
#define pir 12
#define blue 11
#define red 10
#define green 9

int fsr1 = 0;
int fsr2 = 0;
int fsr3 = 0;
int fsr4 = 0;
bool playing = false;
bool called = false;
int pirState = LOW;
int pirSensor = 0;
bool p5loaded = false;
String jsonString = "";
unsigned long gameTime; 

void setup() {
  Serial.begin(9600);
  pinMode(fsrOne, INPUT);
  pinMode(fsrTwo, INPUT);
  pinMode(fsrThree, INPUT);
  pinMode(fsrFour, INPUT);
  pinMode(pir, INPUT);
  gameTime = millis();
  delay(100);
}

void loop() {

    pirSensor = digitalRead(pir);
  
    if (millis() - gameTime > 120000) {
      playing = false;
    }
    
    checkIfStarted();
  
    if (playing){
      lightUpRGB(0,0,255);
      fsr1 = digitalRead(fsrOne);
      fsr2 = digitalRead(fsrTwo);
      fsr3 = digitalRead(fsrThree);
      fsr4 = digitalRead(fsrFour);
  
      if (fsr1 || fsr2 || fsr3 || fsr4){
        gameTime = millis();
      }
      
      jsonString = "{\"fsr1\":"+String(fsr1)+",\"fsr2\":"+String(fsr2)+",\"fsr3\":"+String(fsr3)+",\"fsr4\":"+String(fsr4)+"}";
      Serial.println(jsonString);
    } 
  
  delay(100);
}

void checkIfStarted(){
  
  if (pirSensor && !playing && !called){
     // Send request to p5
     called = true;
     Serial.println("startGame");
        
  } else if (called && !playing) {
     // received confirmation from p5
     lightUpRGB(255,0,0);
     if (Serial.available() > 0){
       playing = Serial.read();
       if (playing == "1"){
         gameTime = millis();
       }
       
       called = false; 
     } 
  }
  
}

void lightUpRGB(byte r,byte g,byte b){
  analogWrite(red, r);
  analogWrite(green, g);
  analogWrite(blue, b);
}
