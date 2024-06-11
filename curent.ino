#include "ACS712.h"

ACS712 sensor(ACS712_05B, A0);

void setup() {
  Serial.begin(9600);
}

void loop() {
  float I = sensor.getCurrentAC();
  
  // Ignoring the value below 0.09
  if (I < 0.09) {
    I = 0;
  }
  
  Serial.println(I);
  delay(300);
}
