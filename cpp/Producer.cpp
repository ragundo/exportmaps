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

// You can always find the latest version of this plugin in Github
// https://github.com/ragundo/exportmaps  

#include "../include/Producer.h"

using namespace exportmaps_plugin;

void Producer::produce_data(MapsExporter& destination, int x, int y, df::world_region_details* ptr_rd){}
void Producer::produce_end(MapsExporter& destination){}

/*****************************************************************************
*****************************************************************************/

void ProducerTemperature::produce_data(MapsExporter& destination, int x, int y, df::world_region_details* ptr_rd)
{
    RegionDetailsBiome rdg(ptr_rd);

    destination.push_temperature(rdg);
}

void ProducerTemperature::produce_end(MapsExporter& destination)
{
    RegionDetailsBiome rdg;

    // Push the data to the producer for the consumers
    destination.push_temperature(rdg);
}

/*****************************************************************************
*****************************************************************************/

void ProducerRainfall::produce_data(MapsExporter& destination, int x, int y, df::world_region_details* ptr_rd)
{
    RegionDetailsBiome rdg(ptr_rd);

    destination.push_rainfall(rdg);
}

void ProducerRainfall::produce_end(MapsExporter& destination)
{
    RegionDetailsBiome rdg;

    // Push the data to the producer for the consumers
    destination.push_rainfall(rdg);
}

/*****************************************************************************
*****************************************************************************/

void ProducerDrainage::produce_data(MapsExporter& destination, int x, int y, df::world_region_details* ptr_rd)
{
    RegionDetailsBiome rdg(ptr_rd);

    destination.push_drainage(rdg);
}

void ProducerDrainage::produce_end(MapsExporter& destination)
{
    RegionDetailsBiome rdg;

    // Push the data to the producer for the consumers
    destination.push_drainage(rdg);
}

/*****************************************************************************
*****************************************************************************/

void ProducerSavagery::produce_data(MapsExporter& destination, int x, int y, df::world_region_details* ptr_rd)
{
    RegionDetailsBiome rdg(ptr_rd);

    destination.push_savagery(rdg);
}

void ProducerSavagery::produce_end(MapsExporter& destination)
{
    RegionDetailsBiome rdg;

    // Push the data to the producer for the consumers
    destination.push_savagery(rdg);
}

/*****************************************************************************
*****************************************************************************/

void ProducerVolcanism::produce_data(MapsExporter& destination, int x, int y, df::world_region_details* ptr_rd)
{
    RegionDetailsBiome rdg(ptr_rd);

    destination.push_volcanism(rdg);
}

void ProducerVolcanism::produce_end(MapsExporter& destination)
{
    RegionDetailsBiome rdg;

    // Push the data to the producer for the consumers
    destination.push_volcanism(rdg);
}

/*****************************************************************************
*****************************************************************************/

void ProducerVegetation::produce_data(MapsExporter& destination, int x, int y, df::world_region_details* ptr_rd)
{
    RegionDetailsBiome rdg(ptr_rd);

    destination.push_vegetation(rdg);
}

void ProducerVegetation::produce_end(MapsExporter& destination)
{
    RegionDetailsBiome rdg;

    // Push the data to the producer for the consumers
    destination.push_vegetation(rdg);
}

/*****************************************************************************
*****************************************************************************/

void ProducerEvilness::produce_data(MapsExporter& destination, int x, int y, df::world_region_details* ptr_rd)
{
    RegionDetailsBiome rdg(ptr_rd);

    destination.push_evilness(rdg);
}

void ProducerEvilness::produce_end(MapsExporter& destination)
{
    RegionDetailsBiome rdg;

    // Push the data to the producer for the consumers
    destination.push_evilness(rdg);
}

/*****************************************************************************
*****************************************************************************/

void ProducerSalinity::produce_data(MapsExporter& destination, int x, int y, df::world_region_details* ptr_rd)
{
    RegionDetailsBiome rdg(ptr_rd);

    destination.push_salinity(rdg);
}

void ProducerSalinity::produce_end(MapsExporter& destination)
{
    RegionDetailsBiome rdg;

    // Push the data to the producer for the consumers
    destination.push_salinity(rdg);
}

/*****************************************************************************
*****************************************************************************/

void ProducerHydro::produce_data(MapsExporter& destination, int x, int y, df::world_region_details* ptr_rd)
{
    RegionDetailsElevationWater rdb(ptr_rd);

    destination.push_hydro(rdb);
}

void ProducerHydro::produce_end(MapsExporter& destination)
{
    RegionDetailsElevationWater rdb;

    // Push the data to the producer for the consumers
    destination.push_hydro(rdb);
}

/*****************************************************************************
*****************************************************************************/

void ProducerElevation::produce_data(MapsExporter& destination, int x, int y, df::world_region_details* ptr_rd)
{
    // Create a copy of the DF data
    RegionDetailsElevation rde(ptr_rd);

    // Push the data to the producer for the consumers
    destination.push_elevation(rde);
}

void ProducerElevation::produce_end(MapsExporter& destination)
{
    RegionDetailsElevation rde;

    // Push the data to the producer for the consumers
    destination.push_elevation(rde);
}

/*****************************************************************************
*****************************************************************************/

void ProducerElevationWater::produce_data(MapsExporter& destination, int x, int y, df::world_region_details* ptr_rd)
{
    // Create a copy of the DF data
    RegionDetailsElevationWater rdew(ptr_rd);

    // Push the data to the producer for the consumers
    destination.push_elevation_water(rdew);
}

void ProducerElevationWater::produce_end(MapsExporter& destination)
{
    RegionDetailsElevationWater rdew;

    // Push the data to the producer for the consumers
    destination.push_elevation_water(rdew);
}

/*****************************************************************************
*****************************************************************************/

void ProducerBiome::produce_data(MapsExporter& destination, int x, int y, df::world_region_details* ptr_rd)
{
    // Create a copy of the DF data
    RegionDetailsBiome rdb(ptr_rd);

    // Push the data to the producer for the consumers
    destination.push_biome(rdb);
}

void ProducerBiome::produce_end(MapsExporter& destination)
{
    RegionDetailsBiome rdb;

    // Push the data to the producer for the consumers
    destination.push_biome(rdb);
}

/*****************************************************************************
*****************************************************************************/

void ProducerGeology::produce_data(MapsExporter& destination, int x, int y, df::world_region_details* ptr_rd)
{
    // Create a copy of the DF data
    RegionDetailsGeology rdg(ptr_rd);

    // Push the data to the producer for the consumers
    destination.push_geology(rdg);
}

void ProducerGeology::produce_end(MapsExporter& destination)
{
    RegionDetailsGeology rdg;

    // Push the data to the producer for the consumers
    destination.push_geology(rdg);
}

/*****************************************************************************
*****************************************************************************/

void ProducerTrading::produce_data(MapsExporter& destination, int x, int y, df::world_region_details* ptr_rd)
{
    // Create a copy of the DF data
    RegionDetailsElevationWater rde(ptr_rd);

    // Push the data to the producer for the consumers
    destination.push_trading(rde);
}

void ProducerTrading::produce_end(MapsExporter& destination)
{
    RegionDetailsElevationWater rdb;

    // Push the data to the producer for the consumers
    destination.push_trading(rdb);
}

/*****************************************************************************
*****************************************************************************/

void ProducerNobility::produce_data(MapsExporter& destination, int x, int y, df::world_region_details* ptr_rd)
{
    // Create a copy of the DF data
    RegionDetailsElevationWater rde(ptr_rd);

    // Push the data to the producer for the consumers
    destination.push_nobility(rde);
}

void ProducerNobility::produce_end(MapsExporter& destination)
{
    RegionDetailsElevationWater rdb;

    // Push the data to the producer for the consumers
    destination.push_nobility(rdb);
}

/*****************************************************************************
*****************************************************************************/

void ProducerDiplomacy::produce_data(MapsExporter& destination, int x, int y, df::world_region_details* ptr_rd)
{
    // Create a copy of the DF data
    RegionDetailsElevationWater rde(ptr_rd);

    // Push the data to the producer for the consumers
    destination.push_diplomacy(rde);
}

void ProducerDiplomacy::produce_end(MapsExporter& destination)
{
    RegionDetailsElevationWater rdb;

    // Push the data to the producer for the consumers
    destination.push_diplomacy(rdb);
}

/*****************************************************************************
*****************************************************************************/

void ProducerSites::produce_data(MapsExporter& destination, int x, int y, df::world_region_details* ptr_rd)
{
    // Create a copy of the DF data
    RegionDetailsElevationWater rde(ptr_rd);

    // Push the data to the producer for the consumers
    destination.push_sites(rde);
}

void ProducerSites::produce_end(MapsExporter& destination)
{
    RegionDetailsElevationWater rdb;

    // Push the data to the producer for the consumers
    destination.push_sites(rdb);
}
