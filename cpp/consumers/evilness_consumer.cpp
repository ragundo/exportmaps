/* zlib.h -- interface of the 'zlib' general purpose compression library
  version 1.2.2, October 3rd, 2004

  Copyright (C) 1995-2004 Jean-loup Gailly and Mark Adler

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  Jean-loup Gailly jloup@gzip.org
  Mark Adler madler@alumni.caltech.edu

*/

#include "../../include/ExportMaps.h"

using namespace exportmaps_plugin;

/*****************************************************************************
External functions
*****************************************************************************/
extern std::pair<int,int> adjust_coordinates_to_region(int x, int y, int delta, int pos_x, int pos_y, int world_width, int world_height);


/*****************************************************************************
Local functions forward declaration
*****************************************************************************/
RGB_color RGB_from_evilness(int evilness);

/*****************************************************************************
Module main function.
This is the function that the thread executes
*****************************************************************************/
void consumer_evilness(void* arg)
{
  MapsExporter* maps_exporter = (MapsExporter*)arg;

  while(arg != nullptr)
  {
    if (maps_exporter->is_evilness_queue_empty())
    {
        // No data on the queue. Sleep 100 ms and try again
        tthread::this_thread::yield();
    }
    else // There's data in the queue
    {
        // Get the data from the queue
        RegionDetailsBiome rdg = maps_exporter->pop_evilness();

        // Check if is the marker for no more data from the producer
        if (rdg.is_end_marker())
        {
          // All the data has been processed. Finish this thread execution
          break;
        }
        else // There's data to be processed
        {
            // Iterate over the 16 subtiles (x) and (y) that a world tile has
            for (auto x=0; x<16; ++x)
                for (auto y=0; y<16; ++y)
                {
                    // Each position of the array is a value that tells us if the local tile
                    // belongs to the NW,N,NE,W,center,E,SW,S,SE world region.
                    // Returns a world coordinate adjusted from the original one
                    std::pair<int,int> adjusted_tile_coordinates = adjust_coordinates_to_region(x,
                                                                                                y,
                                                                                                rdg.get_biome_index(x,y),
                                                                                                rdg.get_pos_x(),
                                                                                                rdg.get_pos_y(),
                                                                                                df::global::world->world_data->world_width,
                                                                                                df::global::world->world_data->world_height);
                    df::region_map_entry& rme = df::global::world->world_data->region_map[adjusted_tile_coordinates.first]
                                                                                         [adjusted_tile_coordinates.second];

                    // Get the RGB values associated to this evilness
                    RGB_color rgb_pixel_color = RGB_from_evilness(rme.evilness);

                    // Write pixels to the bitmap
                    ExportedMapDF* evilness_map = maps_exporter->get_evilness_map();
                    evilness_map->write_world_pixel(rdg.get_pos_x(),
                                                    rdg.get_pos_y(),
                                                    x,
                                                    y,
                                                    rgb_pixel_color);
            }
        }
    }
  }
}

/*****************************************************************************
Utility function
Return the RGB values for the elevation export map given a evilness value.
*****************************************************************************/
RGB_color RGB_from_evilness(int evilness)
{
  unsigned char p =(unsigned char)((((350469331425 * evilness) >> 32) >> 5));
  return RGB_color(p,p,p);
}
