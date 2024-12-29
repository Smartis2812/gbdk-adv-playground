#include <gb/gb.h>

#ifndef GAMEMAP_H
#define GAMEMAP_H

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

void DrawGameMap(void);
UBYTE GetTileData(int8_t x, int8_t y);
void RemoveBitFromTile(uint8_t x, uint8_t y, UBYTE bit);
void SetBitOnTile(uint8_t x, uint8_t y, UBYTE bit);

#endif