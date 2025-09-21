// Author : Andy Bae

// Import libraries

#include <LiquidCrystal.h>

// Set pins
#define alarmPin 8
#define USEcho 10
#define USTrigger 9
#define latchPin 11
#define clockPin 13
#define dataPin 12


float timing = 0.0;
float distance = 0.0;

byte leds = 0;

LiquidCrystal lcd(2,3,4,5,6,7);

void setup() {
  // put your setup code here, to run once:
  pinMode(alarmPin, OUTPUT);
  pinMode(USEcho, INPUT);
  pinMode(USTrigger, OUTPUT);

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);


  Serial.begin(9600);
  Serial.println("Starting the Ultrasonic Alarm System");

  // start lcd display
  lcd.begin(16, 2);
}


void updateShiftRegister()
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
}


void loop() {
  lcd.clear();
  leds = 0;
  digitalWrite(USTrigger, LOW);
  delayMicroseconds(2);
  // put your main code here, to run repeatedly:
  digitalWrite(USTrigger, HIGH);
  delayMicroseconds(10);

  digitalWrite(USTrigger, LOW);

  timing = pulseIn(USEcho, HIGH);
  // Speed of sound is 0.034 : Speed of sound ≈ 343 meters per second at room temperature (20 °C).
  distance = (timing * 0.034) / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print("cm | ");
  Serial.print(distance / 2.54);
  Serial.println("in");

  lcd.setCursor(0, 1);


  if (distance < 100) {
    lcd.print("Distance : ");

    lcd.print(distance, 0);
    lcd.print(" cm");
  } else {
    lcd.print("No Detections");

  }
  
  


  lcd.setCursor(0, 0);
  if (distance <= 20) {
    // turn on middle 3 leds
    lcd.print("WARNING");

    leds = 3;
    updateShiftRegister();
    
    tone(alarmPin, 250);
  }  else if (distance <= 50) {
    // turn on first 3 leds
    lcd.print("DANGER");

    leds = 28;
    updateShiftRegister();
    tone(alarmPin, 150);
  } else {
    lcd.print("NO THREATS");

    leds = 224;
    updateShiftRegister();
    // turn on last 3 leds
    noTone(alarmPin);
  }
  Serial.println(leds);

  delay(300);
}
