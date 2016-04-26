/*
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
*/

// You can always find the latest version of this plugin in Github
// https://github.com/ragundo/exportmaps

#include <set>
#include <modules/World.h>
#include "../include/MapsExporter.h"
#include "../include/RegionDetails.h"
#include "../include/ExportedMap.h"

using namespace DFHack;
using namespace exportmaps_plugin;

//----------------------------------------------------------------------------//
// Calculate how many maps we need to write to disk
//----------------------------------------------------------------------------//
int MapsExporter::get_num_maps_to_write_to_disk()
{
  int result = 0;

  if (maps_to_generate & MapType::TEMPERATURE)                    result++;
  if (maps_to_generate & MapType::RAINFALL)                       result++;
  if (maps_to_generate & MapType::REGION)                         result++;
  if (maps_to_generate & MapType::DRAINAGE)                       result++;
  if (maps_to_generate & MapType::SAVAGERY)                       result++;
  if (maps_to_generate & MapType::VOLCANISM)                      result++;
  if (maps_to_generate & MapType::VEGETATION)                     result++;
  if (maps_to_generate & MapType::EVILNESS)                       result++;
  if (maps_to_generate & MapType::SALINITY)                       result++;
  if (maps_to_generate & MapType::HYDROSPHERE)                    result++;
  if (maps_to_generate & MapType::ELEVATION)                      result++;
  if (maps_to_generate & MapType::ELEVATION_WATER)                result++;
  if (maps_to_generate & MapType::BIOME)                          result++;
  //if (maps_to_generate & MapType::GEOLOGY)                        result++;
  if (maps_to_generate & MapType::TRADING)                        result++;
  if (maps_to_generate & MapType::NOBILITY)                       result++;
  if (maps_to_generate & MapType::DIPLOMACY)                      result++;
  if (maps_to_generate & MapType::SITES)                          result++;
//----------------------------------------------------------------------------//
  if (maps_to_generate_raw & MapTypeRaw::BIOME_TYPE_RAW)          result++;
  if (maps_to_generate_raw & MapTypeRaw::BIOME_REGION_RAW)        result++;
  if (maps_to_generate_raw & MapTypeRaw::DRAINAGE_RAW)            result++;
  if (maps_to_generate_raw & MapTypeRaw::ELEVATION_RAW)           result++;
  if (maps_to_generate_raw & MapTypeRaw::ELEVATION_WATER_RAW)     result++;
  if (maps_to_generate_raw & MapTypeRaw::EVILNESS_RAW)            result++;
  if (maps_to_generate_raw & MapTypeRaw::HYDROSPHERE_RAW)         result++;
  if (maps_to_generate_raw & MapTypeRaw::RAINFALL_RAW)            result++;
  if (maps_to_generate_raw & MapTypeRaw::SALINITY_RAW)            result++;
  if (maps_to_generate_raw & MapTypeRaw::SAVAGERY_RAW)            result++;
  if (maps_to_generate_raw & MapTypeRaw::TEMPERATURE_RAW)         result++;
  if (maps_to_generate_raw & MapTypeRaw::VOLCANISM_RAW)           result++;
  if (maps_to_generate_raw & MapTypeRaw::VEGETATION_RAW)          result++;
//----------------------------------------------------------------------------//
  if (maps_to_generate_hm & MapTypeHeightMap::ELEVATION_HM)       result++;
  if (maps_to_generate_hm & MapTypeHeightMap::ELEVATION_WATER_HM) result++;

  return result;
}

//----------------------------------------------------------------------------//
// Write the generated maps to disk
//----------------------------------------------------------------------------//
void MapsExporter::write_maps_to_disk(Logger& logger)
{
  // Get the number of maps to write
  int num_maps = this->get_num_maps_to_write_to_disk();

  // Number of maps processed
  int i = 0;

  if (maps_to_generate & MapType::TEMPERATURE)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    temperature_map.get()->write_to_disk();
  }

  if (maps_to_generate & MapType::RAINFALL)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    rainfall_map.get()->write_to_disk();
  }

  if (maps_to_generate & MapType::REGION)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    region_map.get()->write_to_disk();
  }

  if (maps_to_generate & MapType::DRAINAGE)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    drainage_map.get()->write_to_disk();
  }

  if (maps_to_generate & MapType::SAVAGERY)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    savagery_map.get()->write_to_disk();
  }

  if (maps_to_generate & MapType::VOLCANISM)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    volcanism_map.get()->write_to_disk();
  }

  if (maps_to_generate & MapType::VEGETATION)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    vegetation_map.get()->write_to_disk();
  }

  if (maps_to_generate & MapType::EVILNESS)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    evilness_map.get()->write_to_disk();
  }

  if (maps_to_generate & MapType::SALINITY)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    salinity_map.get()->write_to_disk();
  }

  if (maps_to_generate & MapType::HYDROSPHERE)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    hydro_map.get()->write_to_disk();
  }

  if (maps_to_generate & MapType::ELEVATION)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    elevation_map.get()->write_to_disk();
  }

  if (maps_to_generate & MapType::ELEVATION_WATER)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    elevation_water_map.get()->write_to_disk();
  }

  if (maps_to_generate & MapType::BIOME)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    biome_map.get()->write_to_disk();
  }

//  if (maps_to_generate & MapType::GEOLOGY)
//  {
//  logger.log_line("Writing maps to disk: ");
//  logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
//    geology_map.get()->write_to_disk();
//  }

  if (maps_to_generate & MapType::TRADING)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    trading_map.get()->write_to_disk();
  }

  if (maps_to_generate & MapType::NOBILITY)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    nobility_map.get()->write_to_disk();
  }

  if (maps_to_generate & MapType::DIPLOMACY)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    diplomacy_map.get()->write_to_disk();
  }

  if (maps_to_generate & MapType::SITES)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    sites_map.get()->write_to_disk();
  }

//----------------------------------------------------------------------------//

  if (maps_to_generate_raw & MapTypeRaw::BIOME_TYPE_RAW)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    biome_type_raw_map.get()->write_to_disk();
  }

  if (maps_to_generate_raw & MapTypeRaw::BIOME_REGION_RAW)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    biome_region_raw_map.get()->write_to_disk();
  }

  if (maps_to_generate_raw & MapTypeRaw::DRAINAGE_RAW)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    drainage_raw_map.get()->write_to_disk();
  }

  if (maps_to_generate_raw & MapTypeRaw::ELEVATION_RAW)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    elevation_raw_map.get()->write_to_disk();
  }

  if (maps_to_generate_raw & MapTypeRaw::ELEVATION_WATER_RAW)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    elevation_water_raw_map.get()->write_to_disk();
  }

  if (maps_to_generate_raw & MapTypeRaw::EVILNESS_RAW)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    evilness_raw_map.get()->write_to_disk();
  }

  if (maps_to_generate_raw & MapTypeRaw::HYDROSPHERE_RAW)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    hydro_raw_map.get()->write_to_disk();
  }

  if (maps_to_generate_raw & MapTypeRaw::RAINFALL_RAW)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    rainfall_raw_map.get()->write_to_disk();
  }

  if (maps_to_generate_raw & MapTypeRaw::SALINITY_RAW)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    salinity_raw_map.get()->write_to_disk();
  }

  if (maps_to_generate_raw & MapTypeRaw::SAVAGERY_RAW)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    savagery_raw_map.get()->write_to_disk();
  }

  if (maps_to_generate_raw & MapTypeRaw::TEMPERATURE_RAW)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    temperature_raw_map.get()->write_to_disk();
  }

  if (maps_to_generate_raw & MapTypeRaw::VOLCANISM_RAW)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    volcanism_raw_map.get()->write_to_disk();
  }

  if (maps_to_generate_raw & MapTypeRaw::VEGETATION_RAW)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    vegetation_raw_map.get()->write_to_disk();
  }


//----------------------------------------------------------------------------//

  if (maps_to_generate_hm & MapTypeHeightMap::ELEVATION_HM)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    elevation_hm_map.get()->write_to_disk();
  }

  if (maps_to_generate_hm & MapTypeHeightMap::ELEVATION_WATER_HM)
  {
    logger.log("Writing maps to disk: ");
    logger.log_number(++i); logger.log(" /"); logger.log_number(num_maps); logger.log_cr();
    elevation_water_hm_map.get()->write_to_disk();
  }

  // Write new line to finish
  logger.log_endl();
}
