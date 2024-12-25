#include <gb/gb.h>
#include <stdint.h>

#include "character.h"
#include "common.h"
#include "maputil.h"

//extern uint8_t PlayerPosition_X;
//extern uint8_t PlayerPosition_Y;

void main(void) {
  DISPLAY_OFF;
  InitCamera(80,48, PALLET_TOWN_MAP_ID);
  SHOW_BKG;
  DISPLAY_ON;

  SetupCharacter();

  while (1) {
    // Game main loop processing goes here
    //UpdateCharacter();

    // Done processing, yield CPU and wait for start of next frame
    vsync();
    // WaitVblLoop(6);
  }
}
