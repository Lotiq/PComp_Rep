#include <FastLED.h>

// pin Numbers can be changed

#define LDR1Analog A1
#define LDR2Analog A2
#define LDR3Analog A3
#define LDR4Analog A4

#define LED_PIN     46
#define NUM_LEDS    64
#define LED_TYPE    WS2813
#define COLOR_ORDER GRB
#define BRIGHTNESS  64

//LEAF 1
#define LED11 29
#define LED12 31
#define LED13 33

//LEAF 2
#define LED21 27
#define LED22 26
#define LED23 25

//LEAF 3
#define LED31 24
#define LED32 23
#define LED33 22

// pump switch pin
#define pumpSw 39
// mist switch pin
#define mistSw 32 

#define NiTiOpen 37
#define NiTiClose 34

int LDR1;
int LDR2;
int LDR3;
int LDR4;

int LDR1Init;
int LDR2Init;
int LDR3Init;
int LDR4Init;

//CRGB leds[NUM_LEDS];

bool energyIncreasing;
byte numActiveLDR;
unsigned long energyTimer = 0; // Records time since last change of energy
int energyTimeStep = 1000; // 1s for each step;
int energyCount = 0; // a counter for energy
int i;
unsigned long flowerTimer = 0; // Records time since flower was activated
bool flowerActive = false; // Save the state of the flower active/non-active
int flowerTimeStep = 25000; // Time for mist
int flowerPHTimeStep = 5000; // Petals Heating time

CRGB leds[NUM_LEDS];

void setup() {
  
  Serial.begin(9600);

  delay(1000);
  LEDS.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  pinMode(LED11, OUTPUT);
  pinMode(LED12, OUTPUT);
  pinMode(LED13, OUTPUT);
  
  pinMode(LED21, OUTPUT);
  pinMode(LED22, OUTPUT);
  pinMode(LED23, OUTPUT);

  pinMode(LED31, OUTPUT);
  pinMode(LED32, OUTPUT);
  pinMode(LED33, OUTPUT);

  pinMode(pumpSw, OUTPUT);
  pinMode(mistSw, OUTPUT);

  pinMode(NiTiOpen, OUTPUT);
  pinMode(NiTiClose, OUTPUT);
  
  // Base values for all LDRs to be compared to
  LDR1Init = analogRead(LDR1Analog);
  LDR2Init = analogRead(LDR2Analog);
  LDR3Init = analogRead(LDR3Analog);
  LDR4Init = analogRead(LDR4Analog);
  
  Serial.print("LDR1Init = ");
  Serial.print(LDR1Init);
  Serial.print(", LDR2Init = ");
  Serial.print(LDR2Init);
  Serial.print(", LDR3Init = ");
  Serial.print(LDR3Init);
  Serial.print(", LDR4Init = ");
  Serial.println(LDR4Init);

  energyTimer = millis();
}

void loop() {
  // Actual values of LDRs
  numActiveLDR = 0;
  LDR1 = analogRead(LDR1Analog);
  //Serial.println(LDR1);
  delay(1);
  LDR2 = analogRead(LDR2Analog);
  //Serial.println(LDR2);
  delay(1);
  LDR3 = analogRead(LDR3Analog);
  //Serial.println(LDR3);
  delay(1);
  LDR4 = analogRead(LDR4Analog);
  //Serial.println(LDR4);
  delay(1);
  //Serial.println('x');
  //Serial.println('x');


  if (-LDR1+LDR1Init > 30){
    numActiveLDR++;
    Serial.println("LDR1 Activated");
    
  }
  if (-LDR2+LDR2Init > 30){
    numActiveLDR++;
    Serial.println("LDR2 Activated");
  }
  if (-LDR3+LDR3Init > 30){
    numActiveLDR++;
    Serial.println("LDR3 Activated");
  }
  if (-LDR4+LDR4Init > 30){
    numActiveLDR++;
    Serial.println("LDR4 Activated");
  }

  if (millis()-energyTimer > energyTimeStep && !flowerActive){ // Checks if enough time has passed or if the flower is currently blossoming
    if (numActiveLDR == 1){
      energyCount++;
      energyIncreasing = true;
    } else if (numActiveLDR >= 2){
      energyCount+=3; // 3 times faster if with 2 Water Cans
      energyIncreasing = true;
    } else {
      energyCount-=3;
      energyIncreasing = false;
    }
    energyTimer = millis(); // update last step time;
  }
  
  if (energyCount < 0){
    energyCount = 0; // prevent the energy going negative
  }
  Serial.println(energyIncreasing);
  
  if (!flowerActive){
    setFiberOptics();
  } else {
    digitalWrite(LED11, HIGH);
    digitalWrite(LED12, HIGH);
    digitalWrite(LED13, HIGH);
    digitalWrite(LED21, HIGH);
    digitalWrite(LED22, HIGH);
    digitalWrite(LED23, HIGH);
    digitalWrite(LED31, HIGH);
    digitalWrite(LED32, HIGH);
    digitalWrite(LED33, HIGH);
  }
  
  if (energyIncreasing) {
    
    // move LED strip up
    
     for (i = 0; i < NUM_LEDS; i++) {
      leds[i - 4].setRGB(0, 0, 0);
      leds[i].setRGB(255, 255, 255);
  
      FastLED.show();
  
      delay(20);
    }
    FastLED.clear();
    
  } else if (!energyIncreasing && energyCount != 0){
    
    for(i=NUM_LEDS;i>0;i--){
      leds[i+4].setRGB(0,0,0);
      leds[i].setRGB(255,255,255);
      FastLED.show();
      delay(20);
    }
    FastLED.clear();
    
  }

  Serial.println(energyIncreasing);
  
  if (energyCount >= 90 && !flowerActive){
    energyCount = 0;
    flowerActive = true;
    flowerTimer = millis();
  }

  if (millis() - flowerTimer > flowerTimeStep && flowerActive){
    flowerActive = false; // when time runs out deactivate the flower
  }

  digitalWrite(pumpSw, LOW);
  digitalWrite(mistSw, LOW);
  digitalWrite(NiTiOpen, LOW);
  digitalWrite(NiTiClose, LOW);
  
  if (flowerActive){
    if (millis()-flowerTimer < flowerPHTimeStep){
      // open the circuit for wire heating for openining
      digitalWrite(NiTiOpen, HIGH);
    } else if (millis()-flowerTimer > flowerTimeStep - flowerPHTimeStep){
      // open the circuit for wire heating for closing
      digitalWrite(NiTiClose, HIGH);
    } else {
      // turn the pump on if niether opening nor closing
      digitalWrite(pumpSw, HIGH);
    }

    digitalWrite(mistSw, HIGH);
  } 
}

void setFiberOptics(){

 if (energyCount >= 10) {
    digitalWrite(LED11, HIGH);
  } else {
    digitalWrite(LED11, LOW);
  }
  
 if (energyCount >= 20) {
    digitalWrite(LED12, HIGH);
  } else {
    digitalWrite(LED12, LOW);
  }

 if (energyCount >= 30) {
    digitalWrite(LED13, HIGH);
  } else {
    digitalWrite(LED13, LOW);
  }

 if (energyCount >= 40) {
    digitalWrite(LED21, HIGH);
  } else {
    digitalWrite(LED21, LOW);
  }

 if (energyCount >= 50) {
    digitalWrite(LED22, HIGH);
  } else {
    digitalWrite(LED22, LOW);
  }

 if (energyCount >= 60) {
    digitalWrite(LED23, HIGH);
  } else {
    digitalWrite(LED23, LOW);
  }

 if (energyCount >= 70) {
    digitalWrite(LED31, HIGH);
  } else {
    digitalWrite(LED31, LOW);
  }

 if (energyCount >= 80) {
    digitalWrite(LED32, HIGH);
  } else {
    digitalWrite(LED32, LOW);
  }

 if (energyCount >= 90) {
    digitalWrite(LED33, HIGH);
  } else {
    digitalWrite(LED33, LOW);
  }
 
}
