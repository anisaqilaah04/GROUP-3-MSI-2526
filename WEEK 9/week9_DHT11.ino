#include "BluetoothSerial.h"
#include <ESP32Servo.h>
#include "DHT.h"

// DHT Setup
#define DHTPIN 4     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);

BluetoothSerial SerialBT;
Servo myServo;

// Pin Definitions
const int servoPin = 18;
const int ledPin = 2;

char command;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_DHT_Control"); 
  
  dht.begin();
  myServo.attach(servoPin);
  pinMode(ledPin, OUTPUT);

  Serial.println("System Initialized. Connect your Smartphone.");
}

void loop() {
  // 1. Reading Sensor Data (Non-blocking timer)
  static unsigned long lastSensorRead = 0;
  if (millis() - lastSensorRead > 2000) { // DHT11 needs ~2 seconds between reads
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
      SerialBT.println("Failed to read from DHT sensor!");
    } else {
      SerialBT.print("Temp: ");
      SerialBT.print(t);
      SerialBT.print("C | Humidity: ");
      SerialBT.print(h);
      SerialBT.println("%");
    }
    lastSensorRead = millis();
  }

  // 2. Receiving Commands
  if (SerialBT.available()) {
    command = SerialBT.read();
    
    switch (command) {
      case '0':
        myServo.write(0);
        SerialBT.println("Servo: 0 degrees");
        break;
      case '1':
        myServo.write(90);
        SerialBT.println("Servo: 90 degrees");
        break;
      case '2':
        myServo.write(180);
        SerialBT.println("Servo: 180 degrees");
        break;
      case 'H':
        digitalWrite(ledPin, HIGH);
        SerialBT.println("LED: ON");
        break;
      case 'L':
        digitalWrite(ledPin, LOW);
        SerialBT.println("LED: OFF");
        break;
    }
  }
}