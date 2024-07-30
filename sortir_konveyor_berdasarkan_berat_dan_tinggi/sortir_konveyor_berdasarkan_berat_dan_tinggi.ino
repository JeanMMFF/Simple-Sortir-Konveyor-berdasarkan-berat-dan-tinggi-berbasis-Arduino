#include <Servo.h>
#include <HX711_ADC.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Servo servo1;
Servo servo2;
Servo servo3;

const int stepPin = 11;
const int dirPin = 2;

HX711_ADC LoadCell(5, 8); //dt , sck
LiquidCrystal_I2C lcd(0x27, 16, 2);

int ir1 = 3;
int ir2 = 6;
int ir3 = 9;
int ir4 = 13;
int val1;
int val2;
int val3;
int val4;

void setup() {
  Serial.begin(9600);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  servo1.attach(4);
  servo2.attach(7);
  servo3.attach(10);
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  LoadCell.begin();
  LoadCell.start(2000);
  LoadCell.setCalFactor(1000);
  lcd.init();
  lcd.backlight();
}

void loop() {


  LoadCell.update();
  float weight = LoadCell.getData();
  delay(5);
  lcd.setCursor(0, 0);
  lcd.print("Weight[g]:");
  lcd.setCursor(0, 1);
  lcd.print(weight);

  val1 = digitalRead(ir1);
  val2 = digitalRead(ir2);
  val3 = digitalRead(ir3);
  val4 = digitalRead(ir4);
  int gerak = 0;

  // Determine movement based on weight and sensor readings
  if (val4 == 1){
    if (weight > 0 && weight < 3) {
      gerak = 1;
    } 
    if (weight > 3 && weight < 6) {
      gerak = 2;
    } 
    if (weight > 6) {
      gerak = 3;
    } 
    digitalWrite(dirPin,LOW); 
    for(int x = 0; x < 400; x++) {
      digitalWrite(stepPin,HIGH); 
      delayMicroseconds(500); 
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(500); 
    }
    delay (3000);
  } else {
    digitalWrite(dirPin,LOW); 
    for(int x = 0; x < 400; x++) {
      digitalWrite(stepPin,HIGH); 
      delayMicroseconds(500); 
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(500);
    }
  }

  // Control servo movements based on gerak values and sensor readings
  if (gerak == 1 && val1 == 1) {
    servo1.write(0);
  } else {
    servo1.write(90);
  }

  if (gerak == 2 && val2 == 1) {
    servo2.write(0);
  } else {
    servo2.write(90);
  }

  if (gerak == 3 && val3 == 1) {
    servo3.write(0);
  } else {
    servo3.write(90);
  }
}
