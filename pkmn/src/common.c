#include <gb/gb.h>


void WaitVblLoop(int8_t i) {
  while (i--) {
    wait_vbl_done();
  }
}