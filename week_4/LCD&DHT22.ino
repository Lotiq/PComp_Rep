#include <LiquidCrystal.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 11  
#define DHTTYPE DHT22

DHT_Unified dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(2,3,4,5,6,7);

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
   dht.begin();
   lcd.begin(16,2);
}

void loop() {
    delay(2000);
  // Get temperature event and print its value.
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  lcd.setCursor(0,0);
  if (isnan(event.temperature)) {
    lcd.print("Error w/ Temp.!");
  }
  else {
    lcd.print("Temp.: ");
    lcd.print(event.temperature);
    lcd.print(" C");
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  lcd.setCursor(0,1);
  if (isnan(event.relative_humidity)) {
    lcd.print("Error w/ Humid.!");
  }
  else {
    lcd.print("Humid.: ");
    lcd.print(event.relative_humidity);
    lcd.print("%");
  }
  // put your main code here, to run repeatedly:
}
