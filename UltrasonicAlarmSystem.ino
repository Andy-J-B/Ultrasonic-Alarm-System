// Author : Andy Bae

// Set pins
#define alarmPin 8
#define USEcho 10
#define USTrigger 9
float timing = 0.0;
float distance = 0.0;

void setup() {
  // put your setup code here, to run once:
  pinMode(alarmPin, OUTPUT);
  pinMode(USEcho, INPUT);
  pinMode(USTrigger, OUTPUT);

  Serial.begin(9600);
  Serial.println("Starting the Ultrasonic Alarm System");
}

void loop() {
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

 
  if (distance <= 50) {
    tone(alarmPin, 500);
  } else {
    noTone(alarmPin);
  }

  delay(100);
}
