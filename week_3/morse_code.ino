#define action 13
#define morse 2
#define yellowLED 8
#define redLED 7
#define greenLED 4

byte pass[] = {1, 1, 0, 1, 0, 0, 1}; // ITP in Morse Code
byte entering = false;
int attempt[100];
byte count = 0;
bool passed = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(morse, INPUT);
  pinMode(action, INPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(action) == HIGH){
    entering = !entering;
    delay(1000);
  }
  if ((!entering)&&(passed)){
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
  }else{
    if (entering){
     digitalWrite(yellowLED,HIGH);
     digitalWrite(redLED, LOW);
     digitalWrite(greenLED, LOW);
      if (digitalRead(morse) == HIGH){
       attempt[count] = 1;
      } else {
       attempt[count] = 0;
      }
      Serial.println(attempt[count]);
      count++;
      delay(1000);
    } else {
      passed = true;
      for (byte j = 0; j<7;j++){
        if (pass[j] != attempt[j]){
          passed = false;
        }
      }
      count = 0;
      memset(attempt, 0, sizeof(attempt));
    }
  }
}
