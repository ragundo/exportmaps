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

#include <algorithm>
#include "../include/ExportMaps.h"
#include "../include/Logger.h"
#include "modules/Filesystem.h"

using namespace std;
using namespace DFHack;

//using df::global::ui;
using df::global::world;

DFHACK_PLUGIN("exportmaps");
DFHACK_PLUGIN_IS_ENABLED(s_enabled);

using namespace exportmaps_plugin;

/*****************************************************************************
Local function definitions
*****************************************************************************/
std::pair<unsigned int, std::vector<int> > process_command_line(std::vector <std::string>& options);

/*****************************************************************************
Plugin global variables
*****************************************************************************/
MapsExporter maps_exporter;


/*****************************************************************************
Here go all the command declarations...
Mostly to allow having the mandatory stuff on top of the file and commands on
the bottom
*****************************************************************************/


/*****************************************************************************
[Optional] Called when the user enables or disables out plugin
*****************************************************************************/
DFhackCExport command_result plugin_enable(color_ostream &out, bool enable)
{
    s_enabled = enable;

    return CR_OK;
}

/*****************************************************************************
This is called right before the plugin library is removed from memory.
*****************************************************************************/
DFhackCExport command_result plugin_shutdown (color_ostream& con)
{
    return CR_OK;
}

/*****************************************************************************
*****************************************************************************/
DFhackCExport command_result plugin_onupdate ( color_ostream& out )
{
    return CR_OK;
}


/*****************************************************************************
Plugin main function
*****************************************************************************/
DFhackCExport command_result exportmaps (color_ostream& con,
                             std::vector <std::string>& parameters)
{
  // Init the loger object
  Logger logger(con);

  // Process command line arguments
  std::pair<unsigned int, std::vector<int> > command_line;
  command_line = process_command_line(parameters);

  // Warn the user about unknown options
  for (unsigned int i = 0; i < command_line.second.size(); ++i)
    if (command_line.second[i] != -1)
      con << "ERROR: unknown command line option: " << parameters[command_line.second[i]] << std::endl;

  // No data can be generated if a world is not loaded, so check it
  if (df::global::world->world_data == nullptr)
  {
    con << "ERROR: no world loaded" << std::endl;
    return CR_OK;
  }

  // Choose what maps to export
  maps_exporter.setup_maps(command_line.first);

  // Begin generating data for the threads(consumers)
  maps_exporter.generate_maps(logger);
  return CR_OK;
}

/*****************************************************************************
[Mandatory] init function. If you have some global state, create it here.
*****************************************************************************/
DFhackCExport command_result plugin_init (color_ostream& con,
                            std::vector <PluginCommand>& commands)
{
    // Fill the command list with your commands.
    commands.push_back(PluginCommand("exportmaps",
                                     "Export world maps to disk while in Fortress Mode",
                                     exportmaps /*,
                                     true or false - true means that the command can't be used from non-interactive user interface'*/));
    return CR_OK;
}

/*****************************************************************************************
Process the command line arguments
returns a pair, where 
 pair.first is a uint bit each bit meaning a map type to be generated
 pair.second is the index to the first wrong argument
 
*****************************************************************************************/
std::pair<unsigned int, std::vector<int> > process_command_line(std::vector <std::string>& options)
{
  unsigned int     maps_to_generate = 0;
  std::vector<int> errors(options.size());

  for ( unsigned int argv_iterator = 0; argv_iterator < options.size(); ++argv_iterator)
  {
    // Get a command line option
    std::string option = options[argv_iterator];
    // Convert to lowercase
    std::transform(option.begin(), option.end(), option.begin(), ::tolower);

    // No error in argument until now
    errors[argv_iterator] = -1;

    if (option == "-all")                                          // All maps
      return std::pair<unsigned int, std::vector<int> >(-1, errors);
    if (option == "-temperature")                                  // map DF style
      maps_to_generate |= MapType::TEMPERATURE;
    else if (option == "-temperature-raw")                         // map raw data file
      maps_to_generate |= MapType::TEMPERATURE_RAW;
    else if (option == "-rainfall")                                // map DF style
      maps_to_generate |= MapType::RAINFALL;
    else if (option == "-rainfall-raw")                            // map raw data file
      maps_to_generate |= MapType::RAINFALL_RAW;
    else if (option == "-drainage")                                // map DF style
      maps_to_generate |= MapType::DRAINAGE;
    else if (option == "-drainage-raw")                            // map raw data file
      maps_to_generate |= MapType::DRAINAGE_RAW;
    else if (option == "-savagery")                                // map DF style
      maps_to_generate |= MapType::SAVAGERY;
    else if (option == "-savagery-raw")                            // map raw data file
      maps_to_generate |= MapType::SALINITY_RAW;
    else if (option == "-volcanism")                               // map DF style
      maps_to_generate |= MapType::VOLCANISM;
    else if (option == "-volcanism-raw")                           // map raw data file
      maps_to_generate |= MapType::VOLCANISM_RAW;
    else if (option == "-vegetation")                              // map DF style
      maps_to_generate |= MapType::VEGETATION;
    else if (option == "-vegetation-raw")                          // map raw data file
      maps_to_generate |= MapType::VEGETATION_RAW;
    else if (option == "-evilness")                                // map DF style
      maps_to_generate |= MapType::EVILNESS;
    else if (option == "-evilness-raw")                            // map raw data file
      maps_to_generate |= MapType::EVILNESS_RAW;
    else if (option == "-salinity")                                // map DF style
      maps_to_generate |= MapType::SALINITY;
    else if (option == "-salinity-raw")                            // map raw data file
      maps_to_generate |= MapType::SALINITY_RAW;
    else if (option == "-hydrosphere")                             // map DF style
      maps_to_generate |= MapType::HYDROSPHERE;
    else if (option == "-hydrosphere-raw")                         // map raw data file
      maps_to_generate |= MapType::HYDROSPHERE_RAW;
    else if (option == "-elevation")                               // map DF style
      maps_to_generate |= MapType::ELEVATION;
    else if (option == "-elevation-raw")                           // map raw data file
      maps_to_generate |= MapType::ELEVATION_RAW;
    else if (option == "-elevation-water")                         // map DF style
      maps_to_generate |= MapType::ELEVATION_WATER;
    else if (option == "-elevation-water-raw")                     // map raw data file
      maps_to_generate |= MapType::ELEVATION_WATER_RAW;
    else if (option == "-biome")                                   // map DF style
      maps_to_generate |= MapType::BIOME;
    else if (option == "-biome-raw")                               // map raw data file
      maps_to_generate |= MapType::BIOME_RAW;
    else if (option == "-trading")                                 // map DF style
      maps_to_generate |= MapType::TRADING;
    else if (option == "-trading-raw")                             // map raw data file
      maps_to_generate |= MapType::TRADING_RAW;
    else if (option == "-nobility")                                // map DF style
      maps_to_generate |= MapType::NOBILITY;
    else if (option == "-nobility-raw")                            // map raw data file
      maps_to_generate |= MapType::NOBILITY_RAW;
    else if (option == "-diplomacy")                                // map DF style
      maps_to_generate |= MapType::DIPLOMACY;
    else if (option == "-diplomacy-raw")                            // map raw data file
      maps_to_generate |= MapType::DIPLOMACY_RAW;
    else if (option == "-sites")                                    // map DF style
      maps_to_generate |= MapType::SITES;
    else if (option == "-sites-raw")                                // map raw data file
      maps_to_generate |= MapType::SITES_RAW;

    else                                                           // ERROR - unknown argument
      errors[argv_iterator] = argv_iterator;
  }
  return std::pair<unsigned int, std::vector<int> >(maps_to_generate, errors);
}
