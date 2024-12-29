#include <gb/gb.h>
#include <gb/metasprites.h>

#include "mathf.h"
#include "gamemap.h"

#include "../gen/background.h"
#include "../gen/exit_sign.h"
#include "../gen/player_sprite.h"
#include "../gen/title.h"


const metasprite_t Player_metasprite[] = {
    {.dy = -8, .dx = -8, .dtile = 0, .props = 0},
    {.dy = 0, .dx = 8, .dtile = 2, .props = 0},
    {.dy = 8, .dx = -8, .dtile = 1, .props = 0},
    {.dy = 0, .dx = 8, .dtile = 3, .props = 0},
    METASPR_TERM};

const metasprite_t PlayerMove_metasprite[] = {
    {.dy = -8, .dx = -8, .dtile = 4, .props = 0},
    {.dy = 0, .dx = 8, .dtile = 6, .props = 0},
    {.dy = 8, .dx = -8, .dtile = 5, .props = 0},
    {.dy = 0, .dx = 8, .dtile = 7, .props = 0},
    METASPR_TERM};

const metasprite_t Exitsign_metasprite[] = {
    {.dy = -8, .dx = -8, .dtile = 0, .props = 0},
    {.dy = 0, .dx = 8, .dtile = 2, .props = 0},
    {.dy = 8, .dx = -8, .dtile = 1, .props = 0},
    {.dy = 0, .dx = 8, .dtile = 3, .props = 0},
    METASPR_TERM};

// The current level of the game
uint8_t Level = 1;
uint8_t LastLevel = 0;

uint8_t PlayerHealth = 8;
uint8_t PlayerX = 0;
uint8_t PlayerY = 7;

uint8_t joy;
UWORD seed;

BOOLEAN CanPlayerMove(uint8_t x, uint8_t y) {
  if (x < 0 || x >= GAMEMAP_WIDTH || y < 0 || y >= GAMEMAP_HEIGHT) {
    return FALSE;
  }
  if (GetTileData(x, y) & WALL_BIT) {
    return FALSE;
  }
  return TRUE;
}

// Update the player position on the GameMap visually

void UpdatePlayerPosition(BOOLEAN isMoving) {
  if (isMoving) {
    move_metasprite_ex(PlayerMove_metasprite, 0, 0, 0,
                       GAMEMAP_OFFSET + (SPRITE_SIZE * (PlayerX + 1)),
                       GAMEMAP_OFFSET * 2 + (SPRITE_SIZE * (PlayerY + 1)));
    wait_vbl_done();  // HACK
    wait_vbl_done();
    wait_vbl_done();
    wait_vbl_done();
  } else {
    move_metasprite_ex(Player_metasprite, 0, 0, 0,
                       GAMEMAP_OFFSET + (SPRITE_SIZE * (PlayerX + 1)),
                       GAMEMAP_OFFSET * 2 + (SPRITE_SIZE * (PlayerY + 1)));
  }
}

void main(void) {
  DISPLAY_ON;
  SHOW_BKG;

  // Load Start screen
  set_bkg_data(0, title_TILE_COUNT, title_tiles);
  set_bkg_tiles(0, 0, 20, 18, title_map);
  // TODO: Animated Title on screen
  // TODO: Animated 'Press Start' on screen

  while (TRUE) {
    joy = joypad();
    if (joy & J_START) {
      break;
    }
    vsync();
  }

  // Load Game play screen
  set_bkg_data(0, background_TILE_COUNT, background_tiles);
  set_bkg_tiles(0, 0, 20, 18, background_map);

  // Load Player sprite
  set_sprite_data(0, 12, player_sprite_tiles);
  UpdatePlayerPosition(FALSE);

  // Load Exit-sign sprite
  set_sprite_data(player_sprite_TILE_COUNT, exit_sign_TILE_COUNT,
                  exit_sign_tiles);
  move_metasprite_ex(Exitsign_metasprite, player_sprite_TILE_COUNT, 0, 4,
                      GAMEMAP_OFFSET + SPRITE_SIZE * GetRandom(1, 8, &seed),
                      GAMEMAP_OFFSET * 2 + SPRITE_SIZE * GetRandom(1, 8, &seed));
                    //  GAMEMAP_OFFSET + SPRITE_SIZE * 8,
                    //  GAMEMAP_OFFSET * 2 + SPRITE_SIZE);
  SHOW_SPRITES;



  BOOLEAN playerMove = FALSE;

  // Game loop
  while (TRUE) {
    if (LastLevel != Level) {
      // Setup new Board
      LastLevel = Level;
    }

    // Move Player
    joy = joypad();
    if (!playerMove) {
      if (joy & J_LEFT) {
        if (CanPlayerMove(PlayerX - 1, PlayerY)) {
          RemoveBitFromTile(PlayerX, PlayerY, PLAYER_BIT);
          PlayerX--;
          SetBitOnTile(PlayerX, PlayerY, PLAYER_BIT);
          playerMove = TRUE;
        }
      } else if (joy & J_RIGHT) {
        if (CanPlayerMove(PlayerX + 1, PlayerY)) {
          RemoveBitFromTile(PlayerX, PlayerY, PLAYER_BIT);
          PlayerX++;
          SetBitOnTile(PlayerX, PlayerY, PLAYER_BIT);
          playerMove = TRUE;
        }
      } else if (joy & J_UP) {
        if (CanPlayerMove(PlayerX, PlayerY - 1)) {
          RemoveBitFromTile(PlayerX, PlayerY, PLAYER_BIT);
          PlayerY--;
          SetBitOnTile(PlayerX, PlayerY, PLAYER_BIT);
          playerMove = TRUE;
        }
      } else if (joy & J_DOWN) {
        if (CanPlayerMove(PlayerX, PlayerY + 1)) {
          RemoveBitFromTile(PlayerX, PlayerY, PLAYER_BIT);
          PlayerY++;
          SetBitOnTile(PlayerX, PlayerY, PLAYER_BIT);
          playerMove = TRUE;
        }
      }
    }

    UpdatePlayerPosition(playerMove);
    playerMove = FALSE;

    if (joy) {
      // Every step costs 1 health
      PlayerHealth--;
    }

    if (PlayerHealth == 0) {
      // Player is dead
    }

    // Check if player is on GameMap Exit

    vsync();
  }
}