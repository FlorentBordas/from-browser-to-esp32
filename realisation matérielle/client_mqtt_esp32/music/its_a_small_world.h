#pragma once

// -------------------------------------------------
// Copyright (c) 2023 HiBit <https://www.hibit.dev>
// -------------------------------------------------

#include "pitches.h"

int its_a_small_world_melody[] = {
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_C5, NOTE_B4, NOTE_B4, NOTE_D4,
  NOTE_E4, NOTE_F4, NOTE_D5, NOTE_B4, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_F4, 
  NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_A4, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_E5, 
  NOTE_D5, NOTE_G4, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_C5, REST, NOTE_C5, REST, NOTE_C5, NOTE_E5, 
  NOTE_C5, NOTE_D5, REST, NOTE_D5, NOTE_D5, NOTE_D5, REST, NOTE_D5, NOTE_F5, NOTE_D5, NOTE_E5, REST, NOTE_E5, 
  NOTE_E5, NOTE_E5, REST, NOTE_E5, NOTE_G5, NOTE_E5, NOTE_F5, REST, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_G4, 
  NOTE_B4, NOTE_C5, NOTE_C5, REST
};

int its_a_small_world_durations[] = {
  8, 8, 4, 4, 4, 8, 8, 4, 4, 4, 8, 8, 4, 4, 4, 8, 8, 4, 4, 4, 8, 8, 4, 8, 8, 4, 8, 8, 4, 
  8, 8, 4, 8, 8, 4, 4, 4, 4, 2, 4, 4, 4, 8, 8, 4, 4, 4, 8, 8, 2, 4, 8, 8, 4, 4, 4, 8, 8, 
  2, 4, 8, 8, 4, 4, 4, 8, 8, 4, 8, 8, 2, 2, 2, 4, 4
};

void play_its_a_small_world(int pin, int note)
{
  //to calculate the note duration, take one second divided by the note type.
  //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
  int duration = 1000 / its_a_small_world_durations[note];
  tone(pin, its_a_small_world_melody[note], duration);

  //to distinguish the notes, set a minimum time between them.
  //the note's duration + 30% seems to work well:
  int pauseBetweenNotes = duration * 1.30;
  delay(pauseBetweenNotes);

  //stop the tone playing:
  noTone(pin);
}