#pragma once

// -------------------------------------------------
// Copyright (c) 2024 HiBit <https://www.hibit.dev>
// -------------------------------------------------

#include "pitches.h"

int the_simpsons_melody[] = {
  NOTE_C4, NOTE_E4, NOTE_FS4, REST, NOTE_A4,
  NOTE_G4, NOTE_E4, NOTE_C4, NOTE_A3,
  NOTE_FS3, NOTE_FS3, NOTE_FS3, NOTE_G3, REST,
  NOTE_FS3, NOTE_FS3, NOTE_FS3, NOTE_G3, NOTE_AS3,
  NOTE_B3, REST
};

int the_simpsons_durations[] = {
  2, 4, 4, 32, 8,
  2, 4, 4, 8,
  8, 8, 8, 4, 2,
  8, 8, 8, 4, 2,
  2, 2
};

void play_the_simpsons(int pin)
{
  int size = sizeof(the_simpsons_durations) / sizeof(int);

  for (int note = 0; note < size; note++) {
    //to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int duration = 1000 / the_simpsons_durations[note];
    tone(pin, the_simpsons_melody[note], duration);

    //to distinguish the notes, set a minimum time between them.
    //the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);

    //stop the tone playing:
    noTone(pin);
  }
}
