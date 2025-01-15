#include <gb/gb.h>
#include "music.h"

void playNote(uint16_t frequency, uint16_t duration) {
    // Set the frequency (NR13 and NR14)
    NR13_REG = frequency & 0xFF;
    NR14_REG = (frequency >> 8) & 0x07;

    // Enable sound channel 1 (NR52, NR51, NR50)
    NR52_REG = 0x80; // Turn on sound
    NR51_REG = 0x11; // Enable sound channel 1
    NR50_REG = 0x77; // Set volume to max

    // Set sound parameters (NR10, NR11, NR12)
    NR10_REG = 0x00; // No sweep
    NR11_REG = 0x80; // Duty cycle 50%
    NR12_REG = 0xF0; // Max volume, no envelope

    // Start the note
    NR14_REG |= 0x80;

    // Wait for the duration of the note
    delay(duration);

    // Stop the note
    NR12_REG = 0x00;
}


Note SongA[] = {
    {C5, 300}, 
    {D5, 300}, 
    {E5, 600}, 
    {C5, 300}, 
    {C5, 300}, 
    {D5, 300}, 
    {E5, 600}, 
    {C5, 300},
    {E5, 300}, 
    {F5, 300}, 
    {G5, 600}, 
    {E5, 300}, 
    {F5, 300}, 
    {G5, 600}
};