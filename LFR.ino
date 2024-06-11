//Sensor
#include "ACS712.h"
ACS712 sensor(ACS712_05B, A4);
#define rs_pin A1
#define ms_pin A2
#define ls_pin A3
#define Sensor A0
float vOUT = 0.0;
float vIN = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
bool mls, ls, ms, rs, mrs, cr, cl;
//Motor Driver
int IN1 = 8;
int IN2 = 9;
int IN3 = 10;
int IN4 = 11;
int ENA = 3;
int ENB = 6;
//Speeds
int LSpeed = 70;       //100             
int adj = 0.134* LSpeed;            //0.134; 
int RSpeed = 72;         //98          //150//120
int turn_reduction = 0.8 * LSpeed;  //0.8
int turn_add = 0.66 * LSpeed;        //100
void setup() {
  Serial.begin(9600);
  pinMode(ls_pin, INPUT);
  pinMode(ms_pin, INPUT);
  pinMode(rs_pin, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}
void loop() {
  readSensors();
  go();
  \\voltage
  int value = analogRead(Sensor);
  vOUT = (value * 5.0) / 1024.0;
  vIN = vOUT / (R2 / (R1 + R2));
  Serial.print("Voltage : ");
  Serial.println(vIN);
  delay(300);
  \\for current
   float I = sensor.getCurrentAC();
  // Ignoring the value below 0.09
  if (I < 0.09) {
    I = 0;
  }
  // frd();
  // left();
  //  right();
  //sharpturn_left();
}
void go() {
  if (ls == LOW && ms == HIGH && rs == LOW) {
    frd();
  } else if ((ls == HIGH || ms == HIGH) && rs == LOW) {
    right();
  } else if (ls == LOW && (ms == HIGH || rs == HIGH)) {
    left();
  }
}
void readSensors() {
  ls = !digitalRead(ls_pin);
  ms = !digitalRead(ms_pin);
  rs = !digitalRead(rs_pin);

  Serial.print(ls);
  Serial.print(ms);
  Serial.println(rs);
}
void frd() {
  analogWrite(ENA, LSpeed);
  analogWrite(ENB, RSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void bck() {
  analogWrite(ENA, LSpeed);
  analogWrite(ENB, RSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void left() {
  analogWrite(ENA, LSpeed - turn_reduction);
  analogWrite(ENB, RSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void right() {
  analogWrite(ENA, LSpeed);
  analogWrite(ENB, RSpeed - turn_reduction);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void sharpturn_right() {
  analogWrite(ENA, LSpeed + turn_add);
  analogWrite(ENB, RSpeed + turn_add);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void sharpturn_left() {
  analogWrite(ENA, LSpeed + turn_add);
  analogWrite(ENB, RSpeed + turn_add - adj);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void stopp() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
