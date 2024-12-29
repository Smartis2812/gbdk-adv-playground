#include <gb/gb.h>

#ifndef GAMEMAP_H
#define GAMEMAP_H

#define GAMEMAP_OFFSET 8
#define GAMEMAP_WIDTH 8
#define GAMEMAP_HEIGHT 8
#define SPRITE_SIZE 16

#define PLAYER_BIT 0x01u     // 0000 0001
#define ENEMY_BIT 0x02u      // 0000 0010
#define ENEMY2_BIT 0x04u     // 0000 0100
#define AMMO_BIT 0x08u       // 0000 1000
#define HEALTH_BIT 0x10u     // 0001 0000
#define BREAKABLE_BIT 0x20u  // 0010 0000
#define WALL_BIT 0x64u       // 0100 0000
#define EXIT_BIT 0x128u      // 1000 0000

void DrawGameMap(void);
BOOLEAN IsFreeTile(int8_t x, int8_t y);
UBYTE GetTileData(int8_t x, int8_t y);
void RemoveBitFromTile(uint8_t x, uint8_t y, UBYTE bit);
void SetBitOnTile(uint8_t x, uint8_t y, UBYTE bit);

#endif