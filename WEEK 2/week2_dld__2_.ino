// --- Individual Pin Definitions ---
// Segments a, b, c, d, e, f, g connected to D2 through D8
const int pinA = 2;
const int pinB = 3;
const int pinC = 4;
const int pinD = 5;
const int pinE = 6;
const int pinF = 8;
const int pinG = 7;

const int incButtonPin = 10;   // Increment button
const int resetButtonPin = 11; // Reset button

// --- Global Variables ---
int count = 0;
int lastIncState = HIGH;   // Assumes external pull-up resistors (HIGH when unpressed)
int lastResetState = HIGH; 

void setup() {
  // Start Serial communication
  Serial.begin(9600);
  
  // Set all segment pins as OUTPUT explicitly
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  
  // Set button pins as INPUT
  pinMode(incButtonPin, INPUT); 
  pinMode(resetButtonPin, INPUT);
  
  // Initialize the display to show 0
  updateDisplay();
}

void loop() {
  // Read current state of both buttons
  int incState = digitalRead(incButtonPin);
  int resetState = digitalRead(resetButtonPin);
  
  // --- Increment Button Logic ---
  if (incState == LOW && lastIncState == HIGH) {
    delay(50); // Debounce
    if (digitalRead(incButtonPin) == LOW) {
      count++;
      if (count > 9) count = 0; 
      updateDisplay();
    }
  }
  
  // --- Reset Button Logic ---
  if (resetState == LOW && lastResetState == HIGH) {
    delay(50); // Debounce
    if (digitalRead(resetButtonPin) == LOW) {
      count = 0;
      updateDisplay();
    }
  }
  
  // Save current states for the next loop
  lastIncState = incState;
  lastResetState = resetState;
}

// Function to update the display using a switch statement instead of an array
void updateDisplay() {
  switch (count) {
    case 0:
      digitalWrite(pinA, LOW); digitalWrite(pinB, LOW); digitalWrite(pinC, LOW);
      digitalWrite(pinD, LOW); digitalWrite(pinE, LOW); digitalWrite(pinF, LOW);
      digitalWrite(pinG, HIGH);
      break;
    case 1:
      digitalWrite(pinA, HIGH);  digitalWrite(pinB, LOW); digitalWrite(pinC, LOW);
      digitalWrite(pinD, HIGH);  digitalWrite(pinE, HIGH);  digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
      break;
    case 2:
      digitalWrite(pinA, LOW); digitalWrite(pinB, LOW); digitalWrite(pinC, HIGH);
      digitalWrite(pinD, LOW); digitalWrite(pinE, LOW); digitalWrite(pinF, HIGH);
      digitalWrite(pinG, LOW);
      break;
    case 3:
      digitalWrite(pinA, LOW); digitalWrite(pinB, LOW); digitalWrite(pinC, LOW);
      digitalWrite(pinD, LOW); digitalWrite(pinE, HIGH);  digitalWrite(pinF, HIGH);
      digitalWrite(pinG, LOW);
      break;
    case 4:
      digitalWrite(pinA, HIGH);  digitalWrite(pinB, LOW); digitalWrite(pinC, LOW);
      digitalWrite(pinD, HIGH);  digitalWrite(pinE, HIGH);  digitalWrite(pinF, LOW);
      digitalWrite(pinG, LOW);
      break;
    case 5:
      digitalWrite(pinA, LOW); digitalWrite(pinB, HIGH);  digitalWrite(pinC, LOW);
      digitalWrite(pinD, LOW); digitalWrite(pinE, HIGH);  digitalWrite(pinF, LOW);
      digitalWrite(pinG, LOW);
      break;
    case 6:
      digitalWrite(pinA, LOW); digitalWrite(pinB, HIGH);  digitalWrite(pinC, LOW);
      digitalWrite(pinD, LOW); digitalWrite(pinE, LOW); digitalWrite(pinF, LOW);
      digitalWrite(pinG, LOW);
      break;
    case 7:
      digitalWrite(pinA, LOW); digitalWrite(pinB, LOW); digitalWrite(pinC, LOW);
      digitalWrite(pinD, HIGH);  digitalWrite(pinE, HIGH);  digitalWrite(pinF, HIGH);
      digitalWrite(pinG, HIGH);
      break;
    case 8:
      digitalWrite(pinA, LOW); digitalWrite(pinB, LOW); digitalWrite(pinC, LOW);
      digitalWrite(pinD, LOW); digitalWrite(pinE, LOW); digitalWrite(pinF, LOW);
      digitalWrite(pinG, LOW);
      break;
    case 9:
      digitalWrite(pinA, LOW); digitalWrite(pinB, LOW); digitalWrite(pinC, LOW);
      digitalWrite(pinD, LOW); digitalWrite(pinE, LOW);  digitalWrite(pinF, LOW);
      digitalWrite(pinG, LOW);
      break;
  }
}