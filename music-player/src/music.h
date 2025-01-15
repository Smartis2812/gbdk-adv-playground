#ifndef MUSIC_H
#define MUSIC_H

#include <gb/gb.h>

#define C4 262
#define C4_SHARP 277
#define D4 294
#define D4_SHARP 311
#define E4 330
#define F4 349
#define F4_SHARP 370
#define G4 392
#define G4_SHARP 415
#define A4 440
#define A4_SHARP 466
#define B4 494
#define C5 523
#define C5_SHARP 554
#define D5 587
#define D5_SHARP 622
#define E5 659
#define F5 698
#define F5_SHARP 740
#define G5 784
#define G5_SHARP 831
#define A5 880
#define A5_SHARP 932
#define B5 988

typedef struct Note {
    uint16_t frequency;
    uint16_t duration;
} Note;

extern Note SongA[14];


void playNote(uint16_t frequency, uint16_t duration);

#endif