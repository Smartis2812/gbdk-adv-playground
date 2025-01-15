#include <gb/gb.h>

// Frequencies for each note from C4 to B5
const uint16_t noteFrequencies[] = {
    262, // C4
    277, // C#4/Db4
    294, // D4
    311, // D#4/Eb4
    330, // E4
    349, // F4
    370, // F#4/Gb4
    392, // G4
    415, // G#4/Ab4
    440, // A4
    466, // A#4/Bb4
    494, // B4
    523, // C5
    554, // C#5/Db5
    587, // D5
    622, // D#5/Eb5
    659, // E5
    698, // F5
    740, // F#5/Gb5
    784, // G5
    831, // G#5/Ab5
    880, // A5
    932, // A#5/Bb5
    988  // B5
};

// Define the song notes and durations (example segment from The Magic Flute)
const uint16_t songNotes[] = {
    523, 587, 659, 523, 523, 587, 659, 523, 659, 698, 784, 659, 698, 784
};
const uint16_t songDurations[] = {
    300, 300, 600, 300, 300, 300, 600, 300, 300, 300, 600, 300, 300, 600
};

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

void main() {
    // Initialize the Game Boy
    DISPLAY_OFF;
    SHOW_BKG;
    DISPLAY_ON;

    // Play each note in the song
    for (uint8_t i = 0; i < sizeof(songNotes)/sizeof(songNotes[0]); i++) {
        playNote(songNotes[i], songDurations[i]);
    }

    // Loop forever
    while (1) {
        wait_vbl_done();
    }
}