#include <gb/gb.h>
#include <stdint.h>

#include "character.h"
#include "pallettown.h"

void WaitVblLoop(int8_t i) {
  while (i--) {
    wait_vbl_done();
  }
}

void main(void) {
  ShowPalletTown();
  SetupCharacter();

  // Loop forever
  while (1) {
    // Game main loop processing goes here
    UpdateCharacter();

    // Done processing, yield CPU and wait for start of next frame
    vsync();
    // WaitVblLoop(6);
  }
}
