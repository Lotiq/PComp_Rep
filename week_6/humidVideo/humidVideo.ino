#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 11  

DHT_Unified dht(DHTPIN, DHT22);

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
   dht.begin();
}

void loop() {
  delay(2000);
  // Get temperature event and print its value.
  sensors_event_t event; 
  /*
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    lcd.print("Error w/ Temp.!");
  }
  else {
    lcd.print("Temp.: ");
    lcd.print(event.temperature);
  }*/
  
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(-1);
  }
  else {
    Serial.println(event.relative_humidity);
  }
}
