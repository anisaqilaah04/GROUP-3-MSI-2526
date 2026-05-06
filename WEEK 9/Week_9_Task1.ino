#include "BluetoothSerial.h"
#include <ESP32Servo.h>

BluetoothSerial SerialBT;
Servo myServo;

// Pin Definitions
const int potPin = 34;   // Analog sensor pin
const int servoPin = 18; // Servo signal pin
const int ledPin = 2;    // Built-in LED

int potValue = 0;
char command;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Control"); 
  
  // Attach the servo to the pin
  myServo.attach(servoPin);
  
  pinMode(ledPin, OUTPUT);
  Serial.println("System Ready. Connect via Bluetooth.");
}

void loop() {
  // 1. Read Sensor Value (Potentiometer)
  potValue = analogRead(potPin);

  // 2. Send Sensor Data to Smartphone every 1 second
  // We use a non-blocking timer logic or a simple delay
  static unsigned long lastSendTime = 0;
  if (millis() - lastSendTime > 1000) {
    SerialBT.print("Sensor Value: ");
    SerialBT.println(potValue);
    lastSendTime = millis();
  }

  // 3. Receive Command to Control Servo/LED
  if (SerialBT.available()) {
    command = SerialBT.read();
    Serial.print("Received: ");
    Serial.println(command);

    switch (command) {
      case '0': // Move Servo to 0 degrees
        myServo.write(0);
        SerialBT.println("Servo set to 0°");
        break;
      case '1': // Move Servo to 90 degrees
        myServo.write(90);
        SerialBT.println("Servo set to 90°");
        break;
      case '2': // Move Servo to 180 degrees
        myServo.write(180);
        SerialBT.println("Servo set to 180°");
        break;
      case 'H': // LED ON
        digitalWrite(ledPin, HIGH);
        break;
      case 'L': // LED OFF
        digitalWrite(ledPin, LOW);
        break;
    }
  }
}