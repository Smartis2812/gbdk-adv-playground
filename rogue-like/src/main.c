#include <gb/gb.h>
#include <gb/metasprites.h>

#include "../gen/background.h"
#include "../gen/exit_sign.h"
#include "../gen/player_sprite.h"
#include "../gen/title.h"

#define GAMEMAP_OFFSET 8
#define GAMEMAP_WIDTH 8
#define GAMEMAP_HEIGHT 8
#define SPRITE_SIZE 16

#define PLAYER_BIT 0x01     // 0000 0001
#define ENEMY_BIT 0x02      // 0000 0010
#define ENEMY2_BIT 0x04     // 0000 0100
#define AMMO_BIT 0x08       // 0000 1000
#define HEALTH_BIT 0x10     // 0001 0000
#define BREAKABLE_BIT 0x20  // 0010 0000
#define WALL_BIT 0x64       // 0100 0000
#define EXIT_BIT 0x128      // 1000 0000

// Clear player bit from current position
// gameMap[playerY][playerX] &= ~PLAYER_BIT;
// Set player bit in new position
// gameMap[newY][newX] |= PLAYER_BIT;

UBYTE GameMap[GAMEMAP_WIDTH][GAMEMAP_HEIGHT] = {
    {0, 0, 0, 0, 0, 0, 0, 8}, {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0}};

const metasprite_t Player_metasprite[] = {
    {.dy = -8, .dx = -8, .dtile = 0, .props = 0},
    {.dy = 0, .dx = 8, .dtile = 2, .props = 0},
    {.dy = 8, .dx = -8, .dtile = 1, .props = 0},
    {.dy = 0, .dx = 8, .dtile = 3, .props = 0},
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

// Draws the sprites on the GameMap
void DrawGameMap(void) {
  uint8_t x, y;
  UBYTE tile;

  for (y = 0; y < GAMEMAP_HEIGHT; y++) {
    for (x = 0; x < GAMEMAP_WIDTH; x++) {
      tile = GameMap[x][y];
      set_sprite_tile(x + y * GAMEMAP_WIDTH, tile);
      move_sprite(x + y * GAMEMAP_WIDTH, x * SPRITE_SIZE, y * SPRITE_SIZE);
    }
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
  set_sprite_data(0, player_sprite_TILE_COUNT, player_sprite_tiles);
  move_metasprite_ex(Player_metasprite, 0, 0, 0,
                     GAMEMAP_OFFSET + (SPRITE_SIZE * (PlayerX + 1)),
                     GAMEMAP_OFFSET * 2 + (SPRITE_SIZE * (PlayerY + 1)));

  // Load Exit-sign sprite
  set_sprite_data(player_sprite_TILE_COUNT, exit_sign_TILE_COUNT, exit_sign_tiles);
  move_metasprite_ex(Exitsign_metasprite, player_sprite_TILE_COUNT, 0, 4,
                     GAMEMAP_OFFSET + SPRITE_SIZE * 8,
                     GAMEMAP_OFFSET * 2 + SPRITE_SIZE);
  SHOW_SPRITES;

  // Game loop
  while (TRUE) {
    if (LastLevel != Level) {
      // Setup new Board
      LastLevel = Level;
    }

    // Move Player
    joy = joypad();
    if (joy & J_LEFT) {
      // Move player left
    } else if (joy & J_RIGHT) {
      // Move player right
    } else if (joy & J_UP) {
      // Move player up
    } else if (joy & J_DOWN) {
      // Move player down
    }

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