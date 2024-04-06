#pragma once

// -------------------------------------------------
// Copyright (c) 2024 HiBit <https://www.hibit.dev>
// -------------------------------------------------

#include "pitches.h"

int maroon5_memories_melody[] = {
  REST, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_B4,
  NOTE_G5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_E5, NOTE_F5, NOTE_G5, REST,
  NOTE_E5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5,
  NOTE_A4, NOTE_A4, REST, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_G4, REST, NOTE_G4,
  NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_C5, NOTE_B4,
  NOTE_G5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_E5, NOTE_F5, NOTE_G5,
  NOTE_E5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5,
  NOTE_A4, NOTE_A4, REST, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_G4, REST, NOTE_G4, NOTE_G4,
  NOTE_A4, NOTE_A4, NOTE_A4, REST, NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_C5, REST,
  REST
};

int maroon5_memories_durations[] = {
  4, 2, 2, 2, 2, 2, 2, 2, 4,
  4, 8, 8, 4, 8, 8, 2, 2,
  4, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 8,
  4, 8, 8, 4, 8, 8, 8, 8, 2, 8, 8,
  8, 8, 4, 4, 4, 1,
  4, 8, 8, 4, 8, 8, 1,
  4, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 8,
  4, 8, 8, 4, 8, 8, 8, 8, 4, 4, 8, 8,
  8, 8, 8, 8, 4, 4, 8, 8, 4, 4, 8, 8,
  1
};

void play_maroon5_memories(int pin)
{
  int size = sizeof(maroon5_memories_durations) / sizeof(int);

  for (int note = 0; note < size; note++) {
    //to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int duration = 1000 / maroon5_memories_durations[note];
    tone(pin, maroon5_memories_melody[note], duration);

    //to distinguish the notes, set a minimum time between them.
    //the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);

    //stop the tone playing:
    noTone(pin);
  }
}
