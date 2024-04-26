#pragma once

// -------------------------------------------------
// Copyright (c) 2023 HiBit <https://www.hibit.dev>
// -------------------------------------------------

#include "pitches.h"

int chevelle_the_red_melody[] = {
  NOTE_DB3, NOTE_EB3, NOTE_DB3, REST, NOTE_E3, NOTE_FS3, NOTE_E3, REST,
  NOTE_DB3, NOTE_EB3, NOTE_DB3, REST, NOTE_A2, REST, NOTE_A2, REST,
  NOTE_DB3, NOTE_EB3, NOTE_DB3, REST, NOTE_E3, NOTE_FS3, NOTE_E3, REST,
  NOTE_DB3, NOTE_EB3, NOTE_DB3, REST, NOTE_A2,
  NOTE_DB3, NOTE_DB3, NOTE_EB3, NOTE_DB3, REST, NOTE_E3, NOTE_E3, NOTE_FS3, NOTE_E3,
  NOTE_DB3, REST, NOTE_DB3, NOTE_EB3, NOTE_DB3, REST, NOTE_A2, NOTE_A2, REST,
  NOTE_DB3, REST, NOTE_DB3, NOTE_EB3, NOTE_DB3, REST, NOTE_E3, REST, NOTE_E3, NOTE_FS3, NOTE_E3, REST,
  NOTE_DB3, REST, NOTE_DB3, NOTE_EB3, NOTE_DB3, REST, NOTE_A2, REST,
  NOTE_DB3, REST, NOTE_DB3, NOTE_EB3, NOTE_DB3, REST, NOTE_E3, REST, NOTE_E3, NOTE_FS3, NOTE_E3, REST,
  NOTE_DB3, REST, NOTE_DB3, NOTE_EB3, NOTE_DB3, REST, NOTE_A2, REST,
  NOTE_DB3, REST, NOTE_DB3, NOTE_EB3, NOTE_DB3, REST, NOTE_E3, REST, NOTE_E3, NOTE_FS3, NOTE_E3, REST,
  NOTE_DB3, REST, NOTE_DB3, NOTE_EB3, NOTE_DB3, REST, NOTE_A2, REST,
  NOTE_DB3, REST, NOTE_DB3, REST, NOTE_DB3, REST, NOTE_DB3, REST, NOTE_DB3, REST, NOTE_DB3, REST,
  NOTE_EB3, REST, NOTE_EB3, REST, NOTE_EB3, REST, NOTE_EB3, REST, NOTE_EB3, REST, NOTE_EB3, REST,
  NOTE_B2, REST, NOTE_B2, REST, NOTE_B2, REST, NOTE_B2, REST, NOTE_B2, REST, NOTE_B2, REST,
  NOTE_B2, REST, NOTE_B2, REST, NOTE_B2, REST, NOTE_B2, REST, NOTE_B2, REST, NOTE_B2, REST,
};

int chevelle_the_red_durations[] = {
  4, 16, 8, 16, 4, 16, 8, 16,
  4, 16, 8, 16, 4, 16, 8, 16,
  4, 16, 16, 8, 4, 16, 8, 16,
  4, 16, 16, 8, 2,
  8, 8, 16, 16, 8, 8, 8, 16, 16, 8,
  16, 16, 8, 16, 16, 8, 4, 8, 8,
  16, 16, 8, 16, 16, 8, 16, 16, 16, 16, 8, 8,
  16, 16, 8, 16, 16, 8, 4, 4,
  16, 16, 8, 16, 16, 8, 16, 16, 16, 16, 8, 8,
  16, 16, 8, 16, 16, 8, 4, 4,
  16, 16, 8, 16, 16, 8, 16, 16, 16, 16, 8, 8,
  16, 16, 8, 16, 16, 8, 4, 4,
  8, 16, 16, 16, 16, 8, 8, 16, 16, 16, 16, 8,
  8, 16, 16, 16, 16, 8, 8, 16, 16, 16, 16, 8,
  8, 16, 16, 16, 16, 8, 8, 16, 16, 16, 16, 8,
  8, 16, 16, 16, 16, 8, 8, 16, 16, 16, 16, 8,
};

void play_chevelle_the_red(int pin, int note)
{
  //to calculate the note duration, take one second divided by the note type.
  //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
  int duration = 1000 / chevelle_the_red_durations[note];
  tone(pin, chevelle_the_red_melody[note], duration);

  //to distinguish the notes, set a minimum time between them.
  //the note's duration + 30% seems to work well:
  int pauseBetweenNotes = duration * 1.30;
  delay(pauseBetweenNotes);

  //stop the tone playing:
  noTone(pin);
}