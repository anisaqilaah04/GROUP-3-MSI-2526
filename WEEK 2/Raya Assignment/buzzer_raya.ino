// Notes and their frequencies
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523

int buzzerPin = 7;

// The melody for "Selamat Hari Raya" (Simplified Chorus)
int melody[] = {
  NOTE_F4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_A4, // Se-la-mat Ha-ri
  NOTE_A4, NOTE_AS4, NOTE_G4,                  // Ra-ya
  NOTE_G4, NOTE_A4, NOTE_F4,                   // Ma-af
  NOTE_F4, NOTE_G4, NOTE_E4,                   // Za-hir
  NOTE_D4, NOTE_E4, NOTE_F4                    // Ba-tin
};

// Note durations: 4 = quarter note, 8 = eighth note, etc.
int noteDurations[] = {
  4, 4, 4, 4, 2, 
  4, 4, 2, 
  4, 4, 2, 
  4, 4, 2, 
  4, 4, 2
};

void setup() {
  // No setup needed for tone()
}

void loop() {
  for (int thisNote = 0; thisNote < 15; thisNote++) {

    // Calculate the note duration
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzerPin, melody[thisNote], noteDuration);

    // To distinguish the notes, set a minimum time between them.
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    
    // Stop the tone before the next note
    noTone(buzzerPin);
  }
  
  delay(2000); // Wait 2 seconds before playing again
}