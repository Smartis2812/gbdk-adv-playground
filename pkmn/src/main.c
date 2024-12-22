#include <gb/gb.h>
#include <stdint.h>
#include "pallettown.h"

void main(void)
{
    ShowPalletTown();

    // Loop forever
    while (1)
    {
        // Game main loop processing goes here

        // Done processing, yield CPU and wait for start of next frame
        vsync();
    }
}
