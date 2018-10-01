
int analogVal = 0;
int mappedVal = 0;
void setup() {
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  analogVal = analogRead(A5);
  mappedVal = map(analogVal, 120,400, 3, 0);
  if (mappedVal == 0){
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
  } else if (mappedVal == 1){
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
  } else if (mappedVal == 2) {
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
  } else if (mappedVal == 3) {
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
  }
  Serial.println(analogVal);
}
