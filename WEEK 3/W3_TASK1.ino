int potPin = A0; 
int ledPin = 9;  // or any digital pin through a 220 Ω resistor 
int potValue = 0; 
 
void setup() { 
  Serial.begin(9600); 
  pinMode(ledPin, OUTPUT); 
} 
 
void loop() { 
  potValue = analogRead(potPin); 
 
  // LED ON if potentiometer > half 
  if (potValue > 512) { 
    digitalWrite(ledPin, HIGH); 
  } else { 
    digitalWrite(ledPin, LOW); 
  } 
 
  // Send potentiometer reading to Python 
  Serial.println(potValue); 
 
  delay(100); // send data every 0.1 s 
}