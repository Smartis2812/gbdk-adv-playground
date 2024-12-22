#include <gb/gb.h>
#include "../gen/pallettown_map.h"
#include "../gen/tileset_0.h"

void ShowPalletTown()
{
    SHOW_BKG;

    set_bkg_data(0, tileset_0_TILE_COUNT, tileset_0_tiles);
    set_bkg_tiles(0, 0, pallettown_map_WIDTH, pallettown_map_HEIGHT, pallettown_map_map);
}