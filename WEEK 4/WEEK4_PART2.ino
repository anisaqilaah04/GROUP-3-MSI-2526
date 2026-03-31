// Part 2 RFID

const int ledPin = 7 ;

void setup() 
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); 
}

void loop() 
{

  if (Serial.available() > 0) {
    char cmd = Serial.read();
    
    if (cmd == '1') {
      digitalWrite(ledPin, HIGH); // Turn LED ON
    } 
    else if (cmd == '0') {
      digitalWrite(ledPin, LOW);  // Turn LED OFF
    }
  }
}
