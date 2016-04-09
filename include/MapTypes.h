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

#ifndef MAPTYPE_H
#define MAPTYPE_H

#include <stdint.h>

namespace exportmaps_plugin
{
  // No C++11 enum class as is not supported by VS2010 :(
  enum MapType : uint32_t
  {
    TEMPERATURE     = 1u <<  0, TEMPERATURE_RAW     = 1u <<  1,
    RAINFALL        = 1u <<  2, RAINFALL_RAW        = 1u <<  3,
    DRAINAGE        = 1u <<  4, DRAINAGE_RAW        = 1u <<  5,
    SAVAGERY        = 1u <<  6, SAVAGERY_RAW        = 1u <<  7,
    VOLCANISM       = 1u <<  8, VOLCANISM_RAW       = 1u <<  9,
    VEGETATION      = 1u << 10, VEGETATION_RAW      = 1u << 11,
    EVILNESS        = 1u << 12, EVILNESS_RAW        = 1u << 13,
    SALINITY        = 1u << 14, SALINITY_RAW        = 1u << 15,
    HYDROSPHERE     = 1u << 16, HYDROSPHERE_RAW     = 1u << 17,
    ELEVATION       = 1u << 18, ELEVATION_RAW       = 1u << 19,
    ELEVATION_WATER = 1u << 20, ELEVATION_WATER_RAW = 1u << 21,
    BIOME           = 1u << 22, BIOME_RAW           = 1u << 23,
    SITES           = 1u << 24, SITES_RAW           = 1u << 25,
    TRADING         = 1u << 26, TRADING_RAW         = 1u << 27,
    NOBILITY        = 1u << 28, NOBILITY_RAW        = 1u << 29,
    DIPLOMACY       = 1u << 30, DIPLOMACY_RAW       = 1u << 31
  };
}

#endif
