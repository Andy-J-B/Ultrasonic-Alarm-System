// Author : Andy Bae

// Import libraries

#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo;

// Set pins
#define alarmPin 8
#define USEcho 10
#define USTrigger 9
#define latchPin 11
#define clockPin 13
#define dataPin 12
#define servoPin 1


float timing = 0.0;
float distance = 0.0;

int servoPos = 0;

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

  myservo.attach(servoPin);
  myservo.write(servoPos);




  // start lcd display
  lcd.begin(16, 2);
}


void updateShiftRegister()
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
}

bool rotateServo = true;
bool increaseDegree = true;


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
    lcd.print("DANGER");

    leds = 3;
    updateShiftRegister();
    rotateServo = false;
    
    tone(alarmPin, 500);
  }  else if (distance <= 50) {
    // turn on first 3 leds
    lcd.print("WARNING");
    rotateServo = false;

    leds = 28;
    updateShiftRegister();
    tone(alarmPin, 250);
  } else {
    lcd.print("NO THREATS");
    rotateServo = true;

    leds = 224;
    updateShiftRegister();
    // turn on last 3 leds
    noTone(alarmPin);
  }


  if (rotateServo) {
    // no threats

    if (increaseDegree) {
      // right
      servoPos += 10;

      if (servoPos >= 180) {
        increaseDegree = false;
      }
    } else {
      servoPos -= 10;
      if (servoPos <= 0 ) {
        increaseDegree = true;
      }
    }

    myservo.write(servoPos);

  }

  delay(300);
}
