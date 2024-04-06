#pragma once

// -------------------------------------------------
// Copyright (c) 2024 HiBit <https://www.hibit.dev>
// -------------------------------------------------

#include "pitches.h"

int drift_melody[] = {
  NOTE_AS4, REST, NOTE_AS4, REST, NOTE_AS4, REST, NOTE_AS4, REST,
  NOTE_AS4, NOTE_B4, NOTE_DS5,
  NOTE_AS4, REST, NOTE_AS4, REST,
  NOTE_AS4, NOTE_B4, NOTE_DS5,
  NOTE_AS4, REST, NOTE_AS4, REST,
  NOTE_AS4, NOTE_B4, NOTE_DS5,
  NOTE_AS4, REST, NOTE_AS4, REST,
  NOTE_AS4, NOTE_B4, NOTE_DS5,
  NOTE_F5, REST, NOTE_F5, REST,
  NOTE_GS5, NOTE_FS5, NOTE_F5,
  NOTE_AS4, REST, NOTE_AS4, REST,
  NOTE_GS5, NOTE_FS5, NOTE_F5,
  NOTE_AS4, REST, NOTE_AS4, REST,
  NOTE_AS4, NOTE_B4, NOTE_DS5,
  NOTE_AS4, REST, NOTE_AS4, REST,
  NOTE_AS4, NOTE_B4, NOTE_DS5,
  NOTE_AS4, REST, NOTE_AS4, REST,
  REST
};

int drift_durations[] = {
  4, 4, 4, 4, 4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  1
};

void play_drift(int pin, int note)
{
  //to calculate the note duration, take one second divided by the note type.
  //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
  int duration = 1000 / drift_durations[note];
  tone(pin, drift_melody[note], duration);

  //to distinguish the notes, set a minimum time between them.
  //the note's duration + 30% seems to work well:
  int pauseBetweenNotes = duration * 1.30;
  delay(pauseBetweenNotes);

  //stop the tone playing:
  noTone(pin);
}