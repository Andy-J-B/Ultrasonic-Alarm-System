// Author : Andy Bae

// Set pins
#define alarmPin 8
#define USEcho 10
#define USTrigger 9
#define firstRedLed 2
#define latchPin 11
#define clockPin 6
#define dataPin 12


float timing = 0.0;
float distance = 0.0;

byte leds = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(alarmPin, OUTPUT);
  pinMode(USEcho, INPUT);
  pinMode(USTrigger, OUTPUT);
  pinMode(firstRedLed, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);


  Serial.begin(9600);
  Serial.println("Starting the Ultrasonic Alarm System");
}


void updateShiftRegister()
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
}


void loop() {
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



  if (distance <= 20) {
    // turn on middle 3 leds
    digitalWrite(firstRedLed, HIGH);
    leds = 3;
    updateShiftRegister();
    
    tone(alarmPin, 250);
  }  else if (distance <= 50) {
    // turn on first 3 leds
    digitalWrite(firstRedLed, LOW);
    leds = 28;
    updateShiftRegister();
    tone(alarmPin, 150);
  } else {
    digitalWrite(firstRedLed, LOW);
    leds = 224;
    updateShiftRegister();
    // turn on last 3 leds
    noTone(alarmPin);
  }
  Serial.println(leds);

  delay(100);
}
