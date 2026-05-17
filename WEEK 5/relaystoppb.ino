const int relay1 = 7;
const int relay2 = 8;      // Fixed: was wrongly declared as relay1
const int buttonPin = 3;
const int ledPin = 2;

void setup()
{
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // Internal pull-up, button reads LOW when pressed
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  if (digitalRead(buttonPin) == LOW)   // Button is pressed
  {
    stopActuator();
    digitalWrite(ledPin, HIGH);        // LED ON
    delay(5000);
  }
  else                                 // Button not pressed
  {
    digitalWrite(ledPin, LOW);         // LED OFF
    extendActuator();
    delay(5000);

    if (digitalRead(buttonPin) == LOW) return; // Check again before retracting

    retractActuator();
    delay(5000);
  }
}

void extendActuator()
{
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
}

void retractActuator()
{
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
}

void stopActuator()
{
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
}