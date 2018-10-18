#define fsrOne 3
#define fsrTwo 4
#define fsrThree 5
#define fsrFour 6
#define pir 10

int fsr1 = 0;
int fsr2 = 0;
int fsr3 = 0;
int fsr4 = 0;
bool playing = false;
int pirState = LOW;
int pirSensor = 0;
String jsonString = "";
unsigned long gameTime; 

void setup() {
  Serial.begin(9600);
  pinMode(fsrOne, INPUT);
  pinMode(fsrTwo, INPUT);
  pinMode(fsrThree, INPUT);
  pinMode(fsrFour, INPUT);
  pinMode(pir, INPUT);
  delay(500);
}

void loop() {

  //pirSensor = digitalRead(pir);
  pirSensor = 1;
  if (pirSensor) {
    if (!playing){
      playing = true;
      Serial.println("game started");
    }
    // if the motion is detected reset timer
    gameTime = millis();
  }

  if (millis() - gameTime > 120000) {
    playing = false;
  }
  
  if (playing){
    fsr1 = digitalRead(fsrOne);
    fsr2 = digitalRead(fsrTwo);
    fsr3 = digitalRead(fsrThree);
    fsr4 = digitalRead(fsrFour);
    if (fsr1 || fsr2 || fsr3 || fsr4){
      gameTime = millis();
    }
    jsonString = "{\"fsr1\":"+String(fsr1)+",\"fsr2\":"+String(fsr2)+",\"fsr3\":"+String(fsr3)+",\"fsr4\":"+String(fsr4)+",\"gamePlaying\":1"+"}";
    Serial.println(jsonString);
  } else {
    jsonString = "{\"gamePlaying\":0}";
    Serial.println(jsonString);
  }

  delay(100);
}
