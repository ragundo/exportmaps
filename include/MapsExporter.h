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

#ifndef MAPSEXPORTER_H
#define MAPSEXPORTER_H

#include <tinythread.h>

#include <memory>
#include <queue>
#include <list>

#include <BitArray.h>

#include "Producer.h"
#include "RegionDetails.h"
#include "ExportedMap.h"
#include "Logger.h"

using namespace std;

namespace exportmaps_plugin
{

  class MapsExporter
  {
      // Producer data queues for each different map
      queue<class RegionDetailsBiome>           temperature_queue;
      queue<class RegionDetailsBiome>           rainfall_queue;
      queue<class RegionDetailsBiome>           drainage_queue;
      queue<class RegionDetailsBiome>           savagery_queue;
      queue<class RegionDetailsBiome>           volcanism_queue;
      queue<class RegionDetailsBiome>           vegetation_queue;
      queue<class RegionDetailsBiome>           evilness_queue;
      queue<class RegionDetailsBiome>           salinity_queue;
      queue<class RegionDetailsElevationWater>  hydro_queue;
      queue<class RegionDetailsElevation>       elevation_queue;
      queue<class RegionDetailsElevationWater>  elevation_water_queue;
      queue<class RegionDetailsBiome>           biome_queue;
      queue<class RegionDetailsGeology>         geology_queue;
      queue<class RegionDetailsElevationWater>  trading_queue;
      queue<class RegionDetailsElevationWater>  nobility_queue;
      queue<class RegionDetailsElevationWater>  diplomacy_queue;
      queue<class RegionDetailsElevationWater>  sites_queue;

      // Enable the generation of each different map
      uint32_t maps_to_generate;
      uint32_t maps_to_generate_extended;

      // Different DF data producer for each map
      unique_ptr<class ProducerTemperature>    temperature_producer;
      unique_ptr<class ProducerRainfall>       rainfall_producer;
      unique_ptr<class ProducerDrainage>       drainage_producer;
      unique_ptr<class ProducerSavagery>       savagery_producer;
      unique_ptr<class ProducerVolcanism>      volcanism_producer;
      unique_ptr<class ProducerVegetation>     vegetation_producer;
      unique_ptr<class ProducerEvilness>       evilness_producer;
      unique_ptr<class ProducerSalinity>       salinity_producer;
      unique_ptr<class ProducerHydro>          hydro_producer;
      unique_ptr<class ProducerElevation>      elevation_producer;
      unique_ptr<class ProducerElevationWater> elevation_water_producer;
      unique_ptr<class ProducerBiome>          biome_producer;
      unique_ptr<class ProducerGeology>        geology_producer;
      unique_ptr<class ProducerTrading>        trading_producer;
      unique_ptr<class ProducerNobility>       nobility_producer;
      unique_ptr<class ProducerDiplomacy>      diplomacy_producer;
      unique_ptr<class ProducerSites>          sites_producer;


      // Pointers to every map that can be exported
      unique_ptr<class ExportedMapDF>  temperature_map;
      unique_ptr<class ExportedMapDF>  rainfall_map;
      unique_ptr<class ExportedMapDF>  drainage_map;
      unique_ptr<class ExportedMapDF>  savagery_map;
      unique_ptr<class ExportedMapDF>  volcanism_map;
      unique_ptr<class ExportedMapDF>  vegetation_map;
      unique_ptr<class ExportedMapDF>  evilness_map;
      unique_ptr<class ExportedMapDF>  salinity_map;
      unique_ptr<class ExportedMapDF>  hydro_map;
      unique_ptr<class ExportedMapDF>  elevation_map;
      unique_ptr<class ExportedMapDF>  elevation_water_map;
      unique_ptr<class ExportedMapDF>  biome_map;
      unique_ptr<class ExportedMapDF>  geology_map;
      unique_ptr<class ExportedMapDF>  trading_map;
      unique_ptr<class ExportedMapDF>  nobility_map;
      unique_ptr<class ExportedMapDF>  diplomacy_map;
      unique_ptr<class ExportedMapDF>  sites_map;

      // Thread synchronization between producer and consumers
      // accessing the different data queues
      tthread::mutex mtx;

      // Threads for each map type
      list<tthread::thread*> consumer_threads;

  public:

    void setup_maps(uint32_t maps_to_generate);

    void cleanup();

    bool generate_maps(Logger& logger);

    void write_maps_to_disk();

    void push_data(df::world_region_details* ptr_rd, int x, int y);

    void push_end();

    // Push methods

    void push_temperature    (RegionDetailsBiome&          rdg);
    void push_rainfall       (RegionDetailsBiome&          rdg);
    void push_drainage       (RegionDetailsBiome&          rdg);
    void push_savagery       (RegionDetailsBiome&          rdg);
    void push_volcanism      (RegionDetailsBiome&          rdg);
    void push_vegetation     (RegionDetailsBiome&          rdg);
    void push_evilness       (RegionDetailsBiome&          rdg);
    void push_salinity       (RegionDetailsBiome&          rdg);
    void push_hydro          (RegionDetailsElevationWater& rdg);
    void push_elevation      (RegionDetailsElevation&      rde);
    void push_elevation_water(RegionDetailsElevationWater& rdew);
    void push_biome          (RegionDetailsBiome&          rdb);
    void push_geology        (RegionDetailsGeology&        rdg);
    void push_trading        (RegionDetailsElevationWater& rdg);
    void push_nobility       (RegionDetailsElevationWater& rdg);        
    void push_diplomacy      (RegionDetailsElevationWater& rdg);
    void push_sites          (RegionDetailsElevationWater& rdg);

    // Pop methods

    RegionDetailsBiome          pop_temperature();
    RegionDetailsBiome          pop_rainfall();
    RegionDetailsBiome          pop_drainage();
    RegionDetailsBiome          pop_savagery();
    RegionDetailsBiome          pop_volcanism();
    RegionDetailsBiome          pop_vegetation();
    RegionDetailsBiome          pop_evilness();
    RegionDetailsBiome          pop_salinity();
    RegionDetailsElevationWater pop_hydro();
    RegionDetailsElevation      pop_elevation();
    RegionDetailsElevationWater pop_elevation_water();
    RegionDetailsBiome          pop_biome();
    RegionDetailsGeology        pop_geology();
    RegionDetailsElevationWater pop_trading();
    RegionDetailsElevationWater pop_nobility();
    RegionDetailsElevationWater pop_diplomacy();
    RegionDetailsElevationWater pop_sites();

    // Maps getters

    ExportedMapDF* get_temperature_map();
    ExportedMapDF* get_rainfall_map();
    ExportedMapDF* get_drainage_map();
    ExportedMapDF* get_savagery_map();
    ExportedMapDF* get_volcanism_map();
    ExportedMapDF* get_vegetation_map();
    ExportedMapDF* get_evilness_map();
    ExportedMapDF* get_salinity_map();
    ExportedMapDF* get_hydro_map();
    ExportedMapDF* get_elevation_map();
    ExportedMapDF* get_elevation_water_map();
    ExportedMapDF* get_biome_map();
    ExportedMapDF* get_geology_map();
    ExportedMapDF* get_trading_map();
    ExportedMapDF* get_nobility_map();
    ExportedMapDF* get_diplomacy_map();
    ExportedMapDF* get_sites_map();

    // Queue status methods

    bool is_temperature_queue_empty();
    bool is_rainfall_queue_empty();
    bool is_drainage_queue_empty();
    bool is_savagery_queue_empty();
    bool is_volcanism_queue_empty();
    bool is_vegetation_queue_empty();
    bool is_evilness_queue_empty();
    bool is_salinity_queue_empty();
    bool is_hydro_queue_empty();
    bool is_elevation_queue_empty();
    bool is_elevation_water_queue_empty();
    bool is_biome_queue_empty();
    bool is_geology_queue_empty();
    bool is_trading_queue_empty();
    bool is_nobility_queue_empty();
    bool is_diplomacy_queue_empty();
    bool is_sites_queue_empty();

    // Thread related methods

    tthread::mutex& get_mutex();
    void            setup_threads();
    void            wait_for_threads();
  };
}

#endif // MAPSEXPORTER_H
