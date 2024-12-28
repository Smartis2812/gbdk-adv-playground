#include <gb/gb.h>

uint8_t GetRandom(uint8_t min, uint8_t max) {
  initrand();
  return min + (rand() % (max - min + 1));
}