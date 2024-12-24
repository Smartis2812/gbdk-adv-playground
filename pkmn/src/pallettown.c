#include <gb/gb.h>

#include "../gen/pallettown_map.h"
#include "../gen/tileset_0.h"

void ShowPalletTown() {
  SHOW_BKG;

  set_bkg_data(0, tileset_0_TILE_COUNT, tileset_0_tiles);
  // *_WIDHT and *_HEIGHT are in pixels, so we need to divide by 8 to get the
  // number of tiles
  set_bkg_tiles(0, 0, pallettown_map_WIDTH >> 3, pallettown_map_HEIGHT >> 3,
                pallettown_map_map);

  // ToDo: Load in Chunks beacuse of the 256x256 tile limit
  // Workaround for now is to use a smaller map
}