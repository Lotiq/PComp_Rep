
int LDR1;
int LDR2;
int LDR3;
int LDR4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  LDR1 = analogRead(A0);
  delay(1);
  LDR2 = analogRead(A1);
  delay(1);
  LDR3 = analogRead(A2);
  delay(1);
  LDR4 = analogRead(A3);
  delay(1);
  Serial.print("LDR1 = ");
  Serial.print(LDR1);
  Serial.print(", ");
  Serial.print("LDR2 = ");
  Serial.print(LDR2);
  Serial.print(", ");
  Serial.print("LDR3 = ");
  Serial.print(LDR3);
  Serial.print(", ");
  Serial.print("LDR4 = ");
  Serial.println(LDR4);
  delay(100);
  // put your main code here, to run repeatedly:

}
