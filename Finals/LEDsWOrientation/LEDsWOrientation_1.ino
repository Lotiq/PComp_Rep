#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55);
 
void setup(void) 
{
  Serial.begin(9600);
  Serial.println("Orientation Sensor Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  delay(1000);
  pinMode(5, OUTPUT);
  bno.setExtCrystalUse(true);
}
 
void loop(void) 
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  bno.getEvent(&event);
  
  /* Display the floating point data */
  Serial.print("X: ");
  Serial.print(event.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event.orientation.y, 4);
  Serial.print("\tZ: ");
  Serial.print(event.orientation.z, 4);
  Serial.println("");

  if (event.orientation.y > -75 && event.orientation.y < -15 && event.orientation.z > 0 && event.orientation.z < 150){
    digitalWrite(5, HIGH);
  } else {
    digitalWrite(5, LOW);
  }
  
  
  delay(100);
}
