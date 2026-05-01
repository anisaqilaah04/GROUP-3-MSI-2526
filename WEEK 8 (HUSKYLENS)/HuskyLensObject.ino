// HuskyLens 29/4 - Object Detection
#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

HUSKYLENS huskylens;
SoftwareSerial mySerial(4, 5); // RX, TX
const int ledPin = 13;

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
  pinMode(ledPin, OUTPUT);
  
  while (!huskylens.begin(mySerial)) {
    Serial.println(F("Begin failed! Check wiring and Protocol (Serial 9600)"));
    delay(500);
  }
  Serial.println("HuskyLens Ready!");
}

void loop() {
  if (!huskylens.request()) {
    // If request fails, we assume no data/nothing seen
    digitalWrite(ledPin, LOW);
    return;
  }

  // Check if any learned objects are visible
  if (huskylens.available()) {
    HUSKYLENSResult result = huskylens.read();
    
    // Check specifically for ID 1
    if (result.ID == 1) {
      Serial.println("Object 1 detected!");
      digitalWrite(ledPin, HIGH); 
    } 
    else {
      // An object is seen, but it's NOT ID 1
      digitalWrite(ledPin, LOW);
    }
  } 
  else {
    // No learned objects are in the camera's view
    digitalWrite(ledPin, LOW);
  }
}
