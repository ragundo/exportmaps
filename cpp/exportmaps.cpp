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

#include <algorithm>
#include "../include/Mac_compat.h"
#include "../include/ExportMaps.h"
#include "../include/Logger.h"
#include "modules/Filesystem.h"
#include "../../../library/include/DFHackVersion.h"
#include "../../../library/include/Core.h"


using namespace std;
using namespace DFHack;

using df::global::world;

static string PLUGIN_VERSION = "0.43.02";


DFHACK_PLUGIN("exportmaps");
DFHACK_PLUGIN_IS_ENABLED(s_enabled);

using namespace exportmaps_plugin;

//----------------------------------------------------------------------------//
// External variables
//----------------------------------------------------------------------------//
extern unsigned int fill_world_region_details_address;
extern unsigned int delete_world_region_details_address;
extern unsigned int delete_world_region_details_vector_address;

extern unsigned int init_world_site_realization_address;
extern unsigned int delete_world_site_realization_address;

//----------------------------------------------------------------------------//
//Local function definitions
//----------------------------------------------------------------------------//
std::tuple<unsigned int,
           unsigned int,
           unsigned int,
           std::vector<int>
          >process_command_line(std::vector <std::string>& options);

//----------------------------------------------------------------------------//
// Plugin global variables
//----------------------------------------------------------------------------//
MapsExporter maps_exporter;


//----------------------------------------------------------------------------//
// Here go all the command declarations...
// Mostly to allow having the mandatory stuff on top of the file and commands on
// the bottom
//----------------------------------------------------------------------------//


//----------------------------------------------------------------------------//
// [Optional] Called when the user enables or disables out plugin
//----------------------------------------------------------------------------//
DFhackCExport command_result plugin_enable(color_ostream &out, bool enable)
{
    s_enabled = enable;

    return CR_OK;
}

//----------------------------------------------------------------------------//
// This is called right before the plugin library is removed from memory.
//----------------------------------------------------------------------------//
DFhackCExport command_result plugin_shutdown (color_ostream& con)
{
    return CR_OK;
}

//----------------------------------------------------------------------------//
DFhackCExport command_result plugin_onupdate ( color_ostream& out )
{
    return CR_OK;
}


//----------------------------------------------------------------------------//
// Plugin main function
//----------------------------------------------------------------------------//
DFhackCExport command_result exportmaps (color_ostream& con,                   // DFHack console
                                         std::vector <std::string>& parameters // Parameters received by the console
                                        )
{
  // Pause DF or it will crash for sure
  CoreSuspender pause;

  // Init the loger object
  Logger logger(con);

  // Process command line arguments
  std::tuple<unsigned int,
             unsigned int,
             unsigned int,
             std::vector<int>
            > command_line;

  // tuple.first is a uint where each bit ON means a graphical map type to be generated
  // tuple.second is a uint ehere each bit ON means a raw map type to be generated
  // tuple.third is a uint ehere each bit ON means a heightmap type to be generated
  // tuple.fourth is a vector with indexes to wrong arguments in the command line
  command_line = process_command_line(parameters);

  // Alias to the vector of index to wrong options
  std::vector<int>& unknown_options = std::get<3>(command_line);

  // Warn the user about unknown options
  for (unsigned int i = 0; i < unknown_options.size(); ++i)
    if (unknown_options[i] != -1)
      con << "ERROR: unknown command line option: " << parameters[unknown_options[i]] << std::endl;

  // No data can be generated if a world is not loaded, so check it
  if (df::global::world->world_data == nullptr)
  {
    con << "ERROR: no world loaded" << std::endl;
    return CR_OK;
  }

  // Choose what maps to export
  maps_exporter.setup_maps(std::get<0>(command_line), // Graphical maps
                           std::get<1>(command_line), // Raw maps
                           std::get<2>(command_line)  // Height maps
                           );

  // Begin generating data for the threads(consumers) and use the logger
  // object for updating the progress to the DFHack console
  maps_exporter.generate_maps(logger);

  // Done
  return CR_OK;
}

//----------------------------------------------------------------------------//
// [Mandatory] init function. If you have some global state, create it here.
//----------------------------------------------------------------------------//
DFhackCExport command_result plugin_init (color_ostream& con,                   // DFHack console
                                          std::vector <PluginCommand>& commands // Parameters received by the console
                                          )
{
    uint32_t addr_1;
    uint32_t addr_2;
    uint32_t addr_3;
    uint32_t addr_4;
    uint32_t addr_5;

    fill_world_region_details_address          = Core::getInstance().vinfo->getAddress("fill_world_region_details");
    delete_world_region_details_address        = Core::getInstance().vinfo->getAddress("delete_world_region_details");
    delete_world_region_details_vector_address = Core::getInstance().vinfo->getAddress("delete_world_region_details_vector");
    init_world_site_realization_address        = Core::getInstance().vinfo->getAddress("init_world_site_realization");
    delete_world_site_realization_address      = Core::getInstance().vinfo->getAddress("delete_world_site_realization");


    if (!fill_world_region_details_address ||
        !delete_world_region_details_address ||
#ifdef WIN32
        !delete_world_region_details_vector_address
#endif
        !init_world_site_realization_address ||
        !delete_world_site_realization_address)
    {
        // The addresses are not in global.xml
        con.print("ERROR: addresses are not present in globals.xml");
        return CR_FAILURE;
    }

    // Fill the command list with your commands.
    commands.push_back(PluginCommand("exportmaps",                                                                        // Plugin name
                                     "Export world maps in different formats to disk in Fortress/Adventure/Legends Mode", // Plugin brief description
                                     exportmaps                                                                           // Subroutine to be executed when the plugin is called
                                     /*,
                                     true or false - true means that the command can't be used from non-interactive user interface'*/
                                     ));



    // Check if the DF version matches the plugin one and load xml config
    // file if necessary
    string df_version = DFHack::Version::df_version();
    if (df_version.compare(PLUGIN_VERSION) != 0)
    {
        // This DF version is different
        con.printerr("ERROR: DFHack version incorrect");
    }

    return CR_OK;
}

//----------------------------------------------------------------------------//
// Process the command line arguments
// returns a tuple, where
// tuple.first is a uint bit each bit meaning a graphical map type to be generated
// tuple.second is a uint bit each bit meaning a raw map type to be generated
// tuple.third is a vector with index to wrong arguments
//----------------------------------------------------------------------------//
std::tuple<unsigned int, unsigned int, unsigned int, std::vector<int> >
process_command_line(std::vector <std::string>& options)
{
  unsigned int     maps_to_generate     = 0; // Graphical maps to generate
  unsigned int     maps_to_generate_raw = 0; // Raw maps to generate
  unsigned int     maps_to_generate_hm  = 0; // Heightmaps to generate
  std::vector<int> errors(options.size());   // Vector with index to wrong command line options

  // Iterate over all the command line options received
  for ( unsigned int argv_iterator = 0; argv_iterator < options.size(); ++argv_iterator)
  {
    // Get a command line option
    std::string option = options[argv_iterator];

    // Convert to lowercase
    std::transform(option.begin(), option.end(), option.begin(), ::tolower);

    // No error in argument until now
    errors[argv_iterator] = -1;

    // Check command line
    if (option == "-all-df")                                       // All DF maps
    {maps_to_generate = -1; continue;}

    if (option == "-all-raw")                                 // All raws maps
    {maps_to_generate_raw = -1; continue;}

    if (option == "-all-hm")                                  // All raws maps
    {maps_to_generate_hm = -1; continue;}

    if (option == "-temperature")                                  // map DF style
      {maps_to_generate |= MapType::TEMPERATURE; continue;}

    if (option == "-rainfall")                                // map DF style
      {maps_to_generate |= MapType::RAINFALL; continue;}

    if (option == "-region")                                  // map DF style
      {maps_to_generate |= MapType::REGION; continue;}

    if (option == "-drainage")                                // map DF style
      {maps_to_generate |= MapType::DRAINAGE; continue;}

    if (option == "-savagery")                                // map DF style
      {maps_to_generate |= MapType::SAVAGERY; continue;}

    if (option == "-volcanism")                               // map DF style
      {maps_to_generate |= MapType::VOLCANISM; continue;}

    if (option == "-vegetation")                              // map DF style
      {maps_to_generate |= MapType::VEGETATION; continue;}

    if (option == "-evilness")                                // map DF style
      {maps_to_generate |= MapType::EVILNESS; continue;}

    if (option == "-salinity")                                // map DF style
      {maps_to_generate |= MapType::SALINITY; continue;}

    if (option == "-hydrosphere")                             // map DF style
      {maps_to_generate |= MapType::HYDROSPHERE; continue;}

    if (option == "-elevation")                               // map DF style
      {maps_to_generate |= MapType::ELEVATION; continue;}

    if (option == "-elevation-water")                         // map DF style
      {maps_to_generate |= MapType::ELEVATION_WATER; continue;}

    if (option == "-biome")                                   // map DF style
      {maps_to_generate |= MapType::BIOME; continue;}

    if (option == "-trading")                                 // map DF style
     { maps_to_generate |= MapType::TRADING; continue;}

    if (option == "-nobility")                                // map DF style
      {maps_to_generate |= MapType::NOBILITY; continue;}

    if (option == "-diplomacy")                               // map DF style
      {maps_to_generate |= MapType::DIPLOMACY; continue;}

    if (option == "-sites")                                   // map DF style
      {maps_to_generate |= MapType::SITES; continue;}


    // Raw maps

    if (option == "-temperature-raw")                         // map raw data file
      {maps_to_generate_raw |= MapTypeRaw::TEMPERATURE_RAW; continue;}

    if (option == "-rainfall-raw")                            // map raw data file
      {maps_to_generate_raw |= MapTypeRaw::RAINFALL_RAW; continue;}

    if (option == "-drainage-raw")                            // map raw data file
      {maps_to_generate_raw |= MapTypeRaw::DRAINAGE_RAW; continue;}

    if (option == "-savagery-raw")                            // map raw data file
      {maps_to_generate_raw |= MapTypeRaw::SAVAGERY_RAW; continue;}

    if (option == "-volcanism-raw")                           // map raw data file
      {maps_to_generate_raw |= MapTypeRaw::VOLCANISM_RAW; continue;}

    if (option == "-vegetation-raw")                          // map raw data file
      {maps_to_generate_raw |= MapTypeRaw::VEGETATION_RAW; continue;}

    if (option == "-evilness-raw")                            // map raw data file
      {maps_to_generate_raw |= MapTypeRaw::EVILNESS_RAW; continue;}

    if (option == "-salinity-raw")                            // map raw data file
      {maps_to_generate_raw |= MapTypeRaw::SALINITY_RAW; continue;}

    if (option == "-hydrosphere-raw")                         // map raw data file
      {maps_to_generate_raw |= MapTypeRaw::HYDROSPHERE_RAW; continue;}

    if (option == "-elevation-raw")                           // map raw data file
      {maps_to_generate_raw |= MapTypeRaw::ELEVATION_RAW; continue;}

    if (option == "-elevation-water-raw")                     // map raw data file
      {maps_to_generate_raw |= MapTypeRaw::ELEVATION_WATER_RAW; continue;}

    if (option == "-biome-raw")                               // map raw data file
    {
      maps_to_generate_raw |= MapTypeRaw::BIOME_TYPE_RAW;
      maps_to_generate_raw |= MapTypeRaw::BIOME_REGION_RAW; continue;
    }

    if (option == "-trading-raw")                             // map raw data file
      {maps_to_generate_raw |= MapTypeRaw::TRADING_RAW; continue;}

    if (option == "-nobility-raw")                            // map raw data file
      {maps_to_generate_raw |= MapTypeRaw::NOBILITY_RAW; continue;}

    if (option == "-diplomacy-raw")                           // map raw data file
      {maps_to_generate_raw |= MapTypeRaw::DIPLOMACY_RAW; continue;}

    if (option == "-sites-raw")                               // map raw data file
      {maps_to_generate_raw |= MapTypeRaw::SITES_RAW; continue;}

    // Heightmaps

    if (option == "-elevation-hm")                            // Heighmap style
      {maps_to_generate_hm |= MapTypeHeightMap::ELEVATION_HM; continue;}

    if (option == "-elevation-water-hm")                      // Heightmap style
      {maps_to_generate_hm |= MapTypeHeightMap::ELEVATION_WATER_HM; continue;}

    // ERROR - unknown argument
      errors[argv_iterator] = argv_iterator;
  }
  return std::tuple<unsigned int,
                    unsigned int,
                    unsigned int,
                    std::vector<int>
                   >(maps_to_generate,
                     maps_to_generate_raw,
                     maps_to_generate_hm,
                     errors
                     );
}
