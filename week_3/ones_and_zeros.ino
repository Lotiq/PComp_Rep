#define action 13
#define ones 3
#define zeros 2
#define yellowLED 8
#define redLED 7
#define greenLED 4

byte pass[] = {1, 1, 0, 1, 0, 0, 1}; // ITP in Morse Code
byte entering = false;
byte attempt[100];
byte count = 0;
bool passed = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(ones, INPUT);
  pinMode(zeros, INPUT);
  pinMode(action, INPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(action) == HIGH){
    if(!entering){
      passed = false;
      memset(attempt, 0, sizeof(attempt));
    }
    entering = !entering;
    delay(1000);
    count = 0;
  }
  if ((!entering)&&(passed)){
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
  }else if ((entering)&&(!passed)){
     digitalWrite(yellowLED,HIGH);
     digitalWrite(redLED, LOW);
     digitalWrite(greenLED, LOW);
      if (digitalRead(ones) == HIGH){
       attempt[count] = 1;
       count++;
       Serial.println("1");
       delay(500);
      } else if (digitalRead(zeros) == HIGH){
       attempt[count] = 0;
       count++;
       Serial.println("0");
       delay(500);
      }
  } else if ((!entering)&&(!passed)){
     digitalWrite(yellowLED,LOW);
     digitalWrite(redLED, HIGH);
     digitalWrite(greenLED, LOW);
  }
  
  if (!entering){
     passed = true;
      for (byte j = 0; j<sizeof(pass);j++){
        if (pass[j] != attempt[j]){
          passed = false;
        }
     }
     for (byte k = sizeof(pass)+1;k<sizeof(attempt);k++){
      if(attempt[k] == 1){
        passed = false;
      }
     }
  }
}
