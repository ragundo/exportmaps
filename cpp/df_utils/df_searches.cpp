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

#include "../../include/dfhack.h"

using namespace std;
using namespace DFHack;

/*****************************************************************************
 Different searches that uses a vector and one id to look for it in the vector
*****************************************************************************/

df::world_site* search_world_data_sites(int target)
{
  vector<df::world_site* >& vec_sites = df::global::world->world_data->sites;

  int start = 0;
  int end = vec_sites.size() - 1;
  while(true)
  {
    int half = (start + end) >> 1;
    int site_id = vec_sites[half]->id;

    if (site_id == target)
      return vec_sites[half];

    if (site_id <= target)
      start = half + 1;
    else
      end = half - 1;

    if (start > end)
      break;
  }
  return nullptr;
};


/*****************************************************************************
*****************************************************************************/

df::historical_entity* search_world_entities(int target)
{
  vector<df::historical_entity* >*  ptr_vec = &df::global::world->entities.all;
  vector<df::historical_entity* >& vec = *ptr_vec;

  int start = 0;
  int end = vec.size() - 1;
  while(true)
  {
    int half = (start + end) >> 1;
    int id = vec[half]->id;

    if (id == target)
      return vec[half];

    if (id <= target)
      start = half + 1;
    else
      end = half - 1;

    if (start > end)
      break;
  }
  return nullptr;
};




/*****************************************************************************
*****************************************************************************/
df::entity_position_assignment* search_entity_positions_assignments(vector<df::entity_position_assignment* >& vec,
                                                                    int                                       target)
{
  int start = 0;
  int end = vec.size() - 1;

  while(true)
  {
    int half = (start + end) >> 1;
    int id = vec[half]->id;

    if (id == target)
      return vec[half];

    if (id <= target)
      start = half + 1;
    else
      end = half - 1;

    if (start > end)
      break;
  }
  return nullptr;
};


/*****************************************************************************
*****************************************************************************/
df::entity_position* search_entity_positions_own(vector<df::entity_position* >& vec,
                                                 int                            target)
{
  int start = 0;
  int end = vec.size() - 1;

  while(true)
  {
    int half = (start + end) >> 1;
    int id = vec[half]->id;

    if (id == target)
      return vec[half];

    if (id <= target)
      start = half + 1;
    else
      end = half - 1;

    if (start > end)
      break;
  }
  return nullptr;
};


/*****************************************************************************
*****************************************************************************/


int get_historical_entity_id_from_world_site(df::world_site* site)
{
  if ( site == nullptr)
    return -1;

  df::entity_site_link* site_link = nullptr;

  for (unsigned int i = 0; i < site->entity_links.size(); i++)
  {
    site_link = site->entity_links[i];
    if ( site_link->anon_6 & 1)
      if (!(site_link->anon_3) && (site_link->anon_4 == -1))
        break;
  }

  if (site_link != nullptr)
  {
    df::historical_entity* ent = search_world_entities(site_link->anon_1);
    if (ent != nullptr)
      return ent->id;
  }

  return -1;
}

/*****************************************************************************
*****************************************************************************/


df::entity_position* search_entity_positions(vector<df::entity_position* >& vec,
                                             int                            target)
{
  int start = 0;
  int end = vec.size() - 1;

  while(true)
  {
    int half = (start + end) >> 1;
    int id = vec[half]->id;

    if (id == target)
      return vec[half];

    if (id <= target)
      start = half + 1;
    else
      end = half - 1;

    if (start > end)
      break;
  }
  return nullptr;
}


/*****************************************************************************
*****************************************************************************/



df::entity_site_link* find_entity_site_link_from_world_site_id(vector<df::entity_site_link* >& vec,
                                                               int                             target)
{
  int start = 0;
  int end = vec.size() - 1;

  while(true)
  {
    int half = (start + end) >> 1;
    int id = vec[half]->target;

    if (id == target)
      return vec[half];

    if (id <= target)
      start = half + 1;
    else
      end = half - 1;

    if (start > end)
      break;
  }
  return nullptr;
};



