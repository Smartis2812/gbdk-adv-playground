#include <gb/gb.h>

#include "../gen/pallettown_map.h"
#include "../gen/tileset_0.h"
#include "common.h"

#define WRAP_SCROLL_Y(y) y
#define SCROLL_Y_OFFSET 0
#define set_submap_indices(x, y, w, h, map, map_w) \
  set_bkg_submap(x, y, w, h, map, map_w)
#define set_submap_attributes(x, y, w, h, map, map_w) \
  set_bkg_submap_attributes(x, y, w, h, map, map_w)
#define MIN(A,B) ((A)<(B)?(A):(B))

#define pallettown_map_mapWidth (pallettown_map_WIDTH/pallettown_map_TILE_W)
#define pallettown_map_mapHeight (pallettown_map_HEIGHT/pallettown_map_TILE_H)

// current and old positions of the camera in pixels
uint16_t camera_x, camera_y, old_camera_x, old_camera_y;
uint16_t map_pos_x, map_pos_y, old_map_pos_x, old_map_pos_y;
uint8_t redraw;

uint16_t camera_max_x, camera_max_y;


inline uint8_t update_column_left(uint8_t map_pos_x)
{
#if (DEVICE_SCREEN_BUFFER_WIDTH == DEVICE_SCREEN_WIDTH)
    return map_pos_x + 1;
#else
    return map_pos_x;
#endif
}

inline uint8_t update_column_right(uint8_t map_pos_x)
{
    return map_pos_x + DEVICE_SCREEN_WIDTH;
}

inline uint8_t update_row_top(uint8_t map_pos_y)
{
#if (DEVICE_SCREEN_BUFFER_HEIGHT == DEVICE_SCREEN_HEIGHT)
    return map_pos_y + 1;
#else
    return map_pos_y;
#endif
}

inline uint8_t update_row_bottom(uint8_t map_pos_y)
{
    return map_pos_y + DEVICE_SCREEN_HEIGHT;
}



/** Sets up the Camera */
void InitCamera(uint8_t x, uint8_t y, uint8_t mapIndex) {
  if (mapIndex == PALLET_TOWN_MAP_ID) {
    // Set up tile data
    // set_native_tile_data(0, bigmap_TILE_COUNT, bigmap_tiles);
    set_native_tile_data(0, tileset_0_TILE_COUNT, tileset_0_tiles);
    camera_max_y = ((pallettown_map_HEIGHT - DEVICE_SCREEN_HEIGHT) * 8) ;
    camera_max_x = ((pallettown_map_WIDTH - DEVICE_SCREEN_WIDTH) * 8) ;
  }

  /*
  if (_cpu == CGB_TYPE) {
          set_bkg_palette(BKGF_CGB_PAL0, bigmap_PALETTE_COUNT,
  bigmap_palettes);
      }*/

  // Initial camera position in pixels set here.
  camera_x = x;
  camera_y = y;

  // Enforce map limits on initial camera position
  if (camera_x > camera_max_x) camera_x = camera_max_x;
  if (camera_y > camera_max_y) camera_y = camera_max_y;
  old_camera_x = camera_x;
  old_camera_y = camera_y;

  map_pos_x = camera_x >> 3;
  map_pos_y = camera_y >> 3;
  old_map_pos_x = old_map_pos_y = 255;
  move_bkg(camera_x, WRAP_SCROLL_Y(camera_y + SCROLL_Y_OFFSET));

  if (mapIndex == PALLET_TOWN_MAP_ID) {
    // Draw the initial map view for the whole screen
    set_submap_indices(
        map_pos_x, map_pos_y,
        MIN(DEVICE_SCREEN_WIDTH + 2u, pallettown_map_mapWidth - map_pos_x),
        MIN(DEVICE_SCREEN_HEIGHT + 2u, pallettown_map_mapHeight - map_pos_y),
        pallettown_map_map, pallettown_map_mapWidth);

    set_submap_attributes(
        map_pos_x, map_pos_y,
        MIN(DEVICE_SCREEN_WIDTH + 2u, pallettown_map_mapWidth - map_pos_x),
        MIN(DEVICE_SCREEN_HEIGHT + 2u, pallettown_map_mapHeight - map_pos_y),
        pallettown_map_map_attributes, pallettown_map_mapWidth);
  }

  redraw = FALSE;

  move_bkg(camera_x, WRAP_SCROLL_Y(camera_y + SCROLL_Y_OFFSET));
}

// void SetCamera(uint8_t x, uint8_t y){
void SetCamera(){
// update hardware scroll position
    move_bkg(camera_x, WRAP_SCROLL_Y(camera_y + SCROLL_Y_OFFSET));
    // up or down
    map_pos_y = (uint8_t)(camera_y >> 3u);
    if (map_pos_y != old_map_pos_y)
    { 
        if (camera_y < old_camera_y)
        {
            set_submap_indices(
                map_pos_x,
                update_row_top(map_pos_y),
                MIN(DEVICE_SCREEN_WIDTH + 2, pallettown_map_mapWidth-map_pos_x),
                2,
                pallettown_map_map,
                pallettown_map_mapWidth);
            set_submap_attributes(
                map_pos_x,
                update_row_top(map_pos_y),
                MIN(DEVICE_SCREEN_WIDTH + 2, pallettown_map_mapWidth-map_pos_x),
                2,
                pallettown_map_map_attributes,
                pallettown_map_mapWidth);
        }
        else
        {
            if ((pallettown_map_mapHeight - DEVICE_SCREEN_HEIGHT) > map_pos_y)
            {
                set_submap_indices(
                    map_pos_x,
                    update_row_bottom(map_pos_y),
                    MIN(DEVICE_SCREEN_WIDTH + 2, pallettown_map_mapWidth-map_pos_x),
                    2,
                    pallettown_map_map,
                    pallettown_map_mapWidth);
                set_submap_attributes(
                    map_pos_x,
                    update_row_bottom(map_pos_y),
                    MIN(DEVICE_SCREEN_WIDTH + 2, pallettown_map_mapWidth-map_pos_x),
                    2,
                    pallettown_map_map_attributes,
                    pallettown_map_mapWidth);
            }
        }
        old_map_pos_y = map_pos_y; 
    }
    // left or right
    map_pos_x = (uint8_t)(camera_x >> 3u);
    if (map_pos_x != old_map_pos_x)
    {
        if (camera_x < old_camera_x)
        {
            set_submap_indices(
                update_column_left(map_pos_x),
                map_pos_y,
                2,
                MIN(DEVICE_SCREEN_HEIGHT + 2, pallettown_map_mapHeight - map_pos_y),
                pallettown_map_map,
                pallettown_map_mapWidth);
            set_submap_attributes(
                update_column_left(map_pos_x),
                map_pos_y,
                2,
                MIN(DEVICE_SCREEN_HEIGHT + 2, pallettown_map_mapHeight - map_pos_y),
                pallettown_map_map_attributes,
                pallettown_map_mapWidth);
        }
        else
        {
            if ((pallettown_map_mapWidth - DEVICE_SCREEN_WIDTH) > map_pos_x)
            {
                set_submap_indices(
                    update_column_right(map_pos_x),
                    map_pos_y,
                    2,
                    MIN(DEVICE_SCREEN_HEIGHT + 2, pallettown_map_mapHeight - map_pos_y),
                    pallettown_map_map,
                    pallettown_map_mapWidth);
                set_submap_attributes(
                    update_column_right(map_pos_x),
                    map_pos_y,
                    2,
                    MIN(DEVICE_SCREEN_HEIGHT + 2, pallettown_map_mapHeight - map_pos_y),
                    pallettown_map_map_attributes,
                    pallettown_map_mapWidth);
            }
        }
        old_map_pos_x = map_pos_x;
    }
    // set old camera position to current camera position
    old_camera_x = camera_x, old_camera_y = camera_y;
}