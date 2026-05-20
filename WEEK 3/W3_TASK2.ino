#include <Servo.h> 
Servo myservo; 

int potPin = A0; 
int ledPin = 9; 
int potValue = 0; 
int angle = 0; 
 
void setup() { 
  Serial.begin(9600); 
  myservo.attach(11); 
  pinMode(ledPin, OUTPUT); 
} 
 
void loop() { 
  // Read potentiometer value (0–1023) 
  potValue = analogRead(potPin); 
 
  // Map pot value to servo angle (0–180) 
  angle = map(potValue, 0, 1023, 0, 180); 
 
  // Move the servo 
  myservo.write(angle); 
 
  // LED control: ON if angle > 90 
  if (angle > 90) { 
    digitalWrite(ledPin, HIGH); 
  } else { 
    digitalWrite(ledPin, LOW); 
  } 
 
  // Send angle to Python 
  Serial.println(angle); 
 
  delay(100); 
}