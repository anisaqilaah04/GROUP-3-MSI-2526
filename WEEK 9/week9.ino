#include "BluetoothSerial.h"
#include <ESP32Servo.h>

Servo myservo;
BluetoothSerial SerialBT;
const int potpin = 34;
const int servo = 18; // servo
const int LED = 2; //Builtin LED
char command;
int potValue = 0,angle;
void setup() 
{
  Serial.begin(115200);                   
  SerialBT.begin("ESP32_CONTROL");         
  Serial.println("Bluetooth initialized... Ready to receive commands.");
  pinMode(LED,OUTPUT);
  myservo.attach(servo);
}

void loop() 
{
  if(SerialBT.available())
  {
    command = SerialBT.read();
    Serial.print("Command received: ");
    Serial.println(command);

    switch (command)
    {
      case 'O':
        digitalWrite(LED,HIGH);break;
      case 'F':
        digitalWrite(LED,LOW);break;
    }

    potValue = analogRead(potpin);
    angle = map(potValue, 0, 1023, 0, 180);
    myservo.write(angle);
    SerialBT.print("PotValue : ");
    SerialBT.print(potValue);
  }
  delay(2000);
}
