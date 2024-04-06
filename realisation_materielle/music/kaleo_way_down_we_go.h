#pragma once

// -------------------------------------------------
// Copyright (c) 2024 HiBit <https://www.hibit.dev>
// -------------------------------------------------

#include "pitches.h"

int kaleo_way_down_we_go_melody[] = {
  NOTE_F4, NOTE_AS5, NOTE_GS4, NOTE_CS4, REST,
  NOTE_AS5, NOTE_AS5, NOTE_CS6, NOTE_AS5, NOTE_AS5, NOTE_GS4, NOTE_F4,
  NOTE_GS4, NOTE_AS5, NOTE_CS6, NOTE_AS5, NOTE_AS5, NOTE_GS4, NOTE_F4, NOTE_GS4,
  NOTE_AS5, NOTE_CS6, NOTE_AS5, NOTE_AS5, NOTE_F5,
  NOTE_DS5, NOTE_CS5, NOTE_AS5, NOTE_AS5, NOTE_AS5,  NOTE_GS4, NOTE_F4, NOTE_GS4,
  NOTE_AS5, NOTE_CS6, NOTE_AS5, NOTE_AS5, NOTE_GS4, NOTE_F4, NOTE_GS4,
  NOTE_AS5, NOTE_CS6, NOTE_AS5, NOTE_AS5, NOTE_GS4, NOTE_F4, NOTE_GS4,
  NOTE_AS5, NOTE_CS6, NOTE_AS5, NOTE_AS5, NOTE_F5,
  NOTE_DS5, NOTE_CS5, NOTE_AS5, NOTE_AS5, NOTE_F5, NOTE_F5, NOTE_F5,
  REST
};

int kaleo_way_down_we_go_durations[] = {
  8, 4, 4, 4, 2,
  4, 4, 4, 2, 4, 4, 4,
  4, 4, 4, 2, 4, 4, 4,
  4, 4, 2, 4, 2,
  8, 8, 4, 2, 4, 4, 4, 4,
  4, 4, 2, 4, 4, 4, 4,
  4, 4, 2, 4, 4, 4, 4,
  4, 4, 2, 4, 2,
  8, 8, 4, 4, 4, 2, 2,
  1
};

void play_kaleo_way_down_we_go(int pin, int note)
{
  //to calculate the note duration, take one second divided by the note type.
  //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
  int duration = 1000 / kaleo_way_down_we_go_durations[note];
  tone(pin, kaleo_way_down_we_go_melody[note], duration);

  //to distinguish the notes, set a minimum time between them.
  //the note's duration + 30% seems to work well:
  int pauseBetweenNotes = duration * 1.30;
  delay(pauseBetweenNotes);

  //stop the tone playing:
  noTone(pin);
}