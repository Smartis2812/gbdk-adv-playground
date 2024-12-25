#include <gb/gb.h>
#include <gb/metasprites.h>

#include "../gen/character_pkmnstadium.h"
#include "../gen/pallettown_map.h"

#define MOVING_PIXELS 16

const metasprite_t TrainerStadium_metasprite_down[] = {
    {.dy = -8, .dx = -8, .dtile = 0, .props = 0},
    {.dy = 0, .dx = 8, .dtile = 2, .props = 0},
    {.dy = 8, .dx = -8, .dtile = 1, .props = 0},
    {.dy = 0, .dx = 8, .dtile = 3, .props = 0},
    METASPR_TERM};

const metasprite_t TrainerStadium_metasprite_down_moving[] = {
    {.dy = -8, .dx = -8, .dtile = 4, .props = 0},
    {.dy = 0, .dx = 8, .dtile = 6, .props = 0},
    {.dy = 8, .dx = -8, .dtile = 5, .props = 0},
    {.dy = 0, .dx = 8, .dtile = 7, .props = 0},
    METASPR_TERM};

const metasprite_t TrainerStadium_metasprite_up[] = {
    {.dy = -8, .dx = -8, .dtile = 8, .props = 0},
    {.dy = 0, .dx = 8, .dtile = 10, .props = 0},
    {.dy = 8, .dx = -8, .dtile = 9, .props = 0},
    {.dy = 0, .dx = 8, .dtile = 11, .props = 0},
    METASPR_TERM};

const metasprite_t TrainerStadium_metasprite_up_moving[] = {
    {.dy = -8, .dx = -8, .dtile = 12, .props = 0},
    {.dy = 0, .dx = 8, .dtile = 14, .props = 0},
    {.dy = 8, .dx = -8, .dtile = 13, .props = 0},
    {.dy = 0, .dx = 8, .dtile = 15, .props = 0},
    METASPR_TERM};

const metasprite_t TrainerStadium_metasprite_left[] = {
    {.dy = -8, .dx = -8, .dtile = 16, .props = 0},
    {.dy = 0, .dx = 8, .dtile = 18, .props = 0},
    {.dy = 8, .dx = -8, .dtile = 17, .props = 0},
    {.dy = 0, .dx = 8, .dtile = 19, .props = 0},
    METASPR_TERM};

const metasprite_t TrainerStadium_metasprite_left_moving[] = {
    {.dy = -8, .dx = -8, .dtile = 20, .props = 0},
    {.dy = 0, .dx = 8, .dtile = 22, .props = 0},
    {.dy = 8, .dx = -8, .dtile = 21, .props = 0},
    {.dy = 0, .dx = 8, .dtile = 23, .props = 0},
    METASPR_TERM};

const metasprite_t TrainerStadium_metasprite_right[] = {
    {.dy = -8, .dx = -8, .dtile = 24, .props = 0},
    {.dy = 0, .dx = 8, .dtile = 26, .props = 0},
    {.dy = 8, .dx = -8, .dtile = 25, .props = 0},
    {.dy = 0, .dx = 8, .dtile = 27, .props = 0},
    METASPR_TERM};

const metasprite_t TrainerStadium_metasprite_right_moving[] = {
    {.dy = -8, .dx = -8, .dtile = 28, .props = 0},
    {.dy = 0, .dx = 8, .dtile = 30, .props = 0},
    {.dy = 8, .dx = -8, .dtile = 29, .props = 0},
    {.dy = 0, .dx = 8, .dtile = 31, .props = 0},
    METASPR_TERM};

// 80x96 starting position
uint8_t sprite_x = 80;
uint8_t sprite_y = 96;
uint8_t is_moving = 0;
uint8_t move_steps = 0;
const metasprite_t *current_metasprite = TrainerStadium_metasprite_down;

void SetupCharacter(void) {
  SHOW_SPRITES;
  set_sprite_data(0, 32, character_pkmnstadium_tiles);
  set_sprite_tile(0, 0);

  move_metasprite_ex(current_metasprite, 0, 0, 0, sprite_x, sprite_y);
}

void UpdateCharacter(void) {
  if (!is_moving) {
    uint8_t joypad_state = joypad();

    if (joypad_state & J_LEFT) {
      current_metasprite = TrainerStadium_metasprite_left_moving;
      is_moving = 1;
      move_steps = MOVING_PIXELS;
    } else if (joypad_state & J_RIGHT) {
      current_metasprite = TrainerStadium_metasprite_right_moving;
      is_moving = 1;
      move_steps = MOVING_PIXELS;
    } else if (joypad_state & J_UP) {
      current_metasprite = TrainerStadium_metasprite_up_moving;
      is_moving = 1;
      move_steps = MOVING_PIXELS;
    } else if (joypad_state & J_DOWN) {
      current_metasprite = TrainerStadium_metasprite_down_moving;
      is_moving = 1;
      move_steps = MOVING_PIXELS;
    }
  }

  if (is_moving) {
    if (move_steps > 0) {
      if (current_metasprite == TrainerStadium_metasprite_left_moving)
        sprite_x -= 1;
      else if (current_metasprite == TrainerStadium_metasprite_right_moving)
        sprite_x += 1;
      else if (current_metasprite == TrainerStadium_metasprite_up_moving)
        sprite_y -= 1;
      else if (current_metasprite == TrainerStadium_metasprite_down_moving)
        sprite_y += 1;

      move_steps--;

      move_metasprite_ex(current_metasprite, 0, 0, 0, sprite_x, sprite_y);
    } else {
      is_moving = 0;  // Movement is done

      if (current_metasprite == TrainerStadium_metasprite_left_moving)
        current_metasprite = TrainerStadium_metasprite_left;
      else if (current_metasprite == TrainerStadium_metasprite_right_moving)
        current_metasprite = TrainerStadium_metasprite_right;
      else if (current_metasprite == TrainerStadium_metasprite_up_moving)
        current_metasprite = TrainerStadium_metasprite_up;
      else if (current_metasprite == TrainerStadium_metasprite_down_moving)
        current_metasprite = TrainerStadium_metasprite_down;

      move_metasprite_ex(current_metasprite, 0, 0, 0, sprite_x, sprite_y);
      //UpdateCamera(sprite_x, sprite_y);
    }

    // wait_vbl_done();
  }

  wait_vbl_done();
}