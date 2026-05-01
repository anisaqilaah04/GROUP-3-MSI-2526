// HuskyLens 29/4 - Color Detection

#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

HUSKYLENS huskylens;
SoftwareSerial mySerial(4, 5); // RX, TX

// RGB LED Pin Definitions
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
  
  // Initialize RGB pins as outputs
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  
  while (!huskylens.begin(mySerial)) {
    Serial.println(F("Begin failed!"));
    delay(500);
  }
  Serial.println("HuskyLens Color Recognition Ready!");
}

void loop() {
  if (!huskylens.request()) {
    // If no communication, turn off LED
    setRGB(0, 0, 0); 
    return;
  }
  
  if (huskylens.available()) {
    HUSKYLENSResult result = huskylens.read();
    
    if (result.command == COMMAND_RETURN_BLOCK) {
      // Sync the HW-479 RGB LED with the detected ID
      switch (result.ID) {
        case 1: // RED
          Serial.println("Color RED is detected");
          setRGB(255, 0, 0);
          break;
        case 2: // BLUE
          Serial.println("Color BLUE is detected");
          setRGB(0, 0, 255);
          break;
        case 3: // GREEN
          Serial.println("Color GREEN is detected");
          setRGB(0, 255, 0);
          break;
        default:
          Serial.println("Unknown Color detected");
          setRGB(0, 0, 0); // Turn off for unknown IDs
          break;
      }
    }
  } else {
    // If nothing is in the camera's view, turn the LED off
    setRGB(0, 0, 0);
  }
}

// Function to control the HW-479 RGB LED
void setRGB(int r, int g, int b) {
  analogWrite(RED_PIN, r);
  analogWrite(GREEN_PIN, g);
  analogWrite(BLUE_PIN, b);
}