#define LDROne A0
#define LDRTwo A1
#define LDRThree A2
int LDR1;
int LDR2;
int LDR3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  LDR1 = analogRead(LDROne);
  delay(1);
  LDR2 = analogRead(LDRTwo);
  delay(1);
  LDR3 = analogRead(LDRThree);
  delay(1);
  Serial.print("LDR1 = ");
  Serial.print(LDR1);
  Serial.print(", ");
  Serial.print("LDR2 = ");
  Serial.print(LDR2);
  Serial.print(", ");
  Serial.print("LDR3 = ");
  Serial.println(LDR3);

  // put your main code here, to run repeatedly:

}
