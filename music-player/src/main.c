#include <gb/gb.h>

#include "music.h"

void main(void) {
  DISPLAY_OFF;
  SHOW_BKG;
  DISPLAY_ON;

  while (1) {
    // Play each note in the SongA
    for (uint8_t i = 0; i < sizeof(SongA) / sizeof(SongA[0]); i++) {
      playNote(SongA[i].frequency, SongA[i].duration);
    }

    vsync();
  }
}