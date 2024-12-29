#include "gamemap.h"

#include <gb/gb.h>

// clang-format off

// The GameMap data
UBYTE GameMap[GAMEMAP_HEIGHT][GAMEMAP_WIDTH] = {
    {0, 0, 0, 0, 0, 0, 0, 8}, 
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}, 
    {1, 0, 0, 0, 0, 0, 0, 0}}
;
// clang-format on

// Draws the sprites on the GameMap
void DrawGameMap(void) {
  uint8_t x, y;
  UBYTE tile;

  for (y = 0; y < GAMEMAP_HEIGHT; y++) {
    for (x = 0; x < GAMEMAP_WIDTH; x++) {
      tile = GameMap[y][x];
      set_sprite_tile(x + y * GAMEMAP_WIDTH, tile);
      move_sprite(x + y * GAMEMAP_WIDTH, x * SPRITE_SIZE, y * SPRITE_SIZE);
    }
  }
}

// Gets the tile data at the given x and y position from the GameMap
UBYTE GetTileData(int8_t x, int8_t y) {
  if (x < 0 || x >= GAMEMAP_WIDTH || y < 0 || y >= GAMEMAP_HEIGHT) {
    return 0;
  }
  return GameMap[y][x];
}

void RemoveBitFromTile(uint8_t x, uint8_t y, UBYTE bit) {
  GameMap[y][x] &= ~bit;
}

void SetBitOnTile(uint8_t x, uint8_t y, UBYTE bit) { GameMap[y][x] |= bit; }