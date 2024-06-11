#define Sensor A0
float vOUT = 0.0;
float vIN = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;

void setup() {
  Serial.begin(9600);
}
void loop() {
  int value = analogRead(Sensor);
  vOUT = (value * 5.0) / 1024.0;
  vIN = vOUT / (R2 / (R1 + R2));
  Serial.print("Voltage : ");
  Serial.println(vIN);
  delay(300);
}
