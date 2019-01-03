#include "DTH_PHSensor.h"

#define PH_SENSOR_PIN A1

DTH_PHSensor pHSensor(PH_SENSOR_PIN);
float ph_val = 0;
float volt = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Test pH sensor by Duy Huynh"); 
}

void loop() {
  // put your main code here, to run repeatedly:
  ph_val = pHSensor.readPH();
  Serial.print("PH value: ");
  Serial.println(ph_val);
  volt = pHSensor.getVoltage();
  Serial.print("PH voltage: ");
  Serial.println(volt);
  delay(2000);
}
