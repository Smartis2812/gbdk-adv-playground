#include <gb/gb.h>
#include <stdint.h>

#include "character.h"
#include "common.h"
#include "maputil.h"

//extern uint8_t PlayerPosition_X;
//extern uint8_t PlayerPosition_Y;

extern uint16_t camera_x, camera_y;
extern uint8_t redraw;
extern uint16_t camera_max_x, camera_max_y;

uint8_t joy;


void main(void) {
  DISPLAY_OFF;
  InitCamera(80,48, PALLET_TOWN_MAP_ID);
  SHOW_BKG;
  DISPLAY_ON;

  SetupCharacter();

  while (1) {
    
    joy = joypad();
        // up or down
        if (joy & J_UP) {
            if (camera_y) {
                camera_y-=16;
                redraw = TRUE;
            }
        } else if (joy & J_DOWN) {
            if (camera_y < camera_max_y) {
                camera_y+=16;
                redraw = TRUE;
            }
        } 
        // left or right
        if (joy & J_LEFT) {
            if (camera_x) {
                camera_x-=16;
                redraw = TRUE;
            }
        } else if (joy & J_RIGHT) {
            if (camera_x < camera_max_x) {
                camera_x+=16;
                redraw = TRUE;
            }
        } 
        if (redraw) {
            vsync();
            SetCamera();
            redraw = FALSE;
            wait_vbl_done();
            wait_vbl_done();
        } else vsync();

  }
}
