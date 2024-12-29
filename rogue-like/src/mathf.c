#include <gb/gb.h>
#include <rand.h>


uint8_t GetRandom(uint8_t min, uint8_t max, UWORD *seed) {
  *seed = DIV_REG;
  *seed |= (UWORD)DIV_REG << 8;
  initrand(*seed);

  if (min >= max) {
    return min;
  }

  uint8_t range = max - min + 1;
  uint8_t rand_num = (uint8_t)(rand() % range);
  return rand_num + min;
}