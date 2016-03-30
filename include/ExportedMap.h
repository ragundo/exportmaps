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

#ifndef EXPORTED_MAP_H
#define EXPORTED_MAP_H

#include <stdint.h>
#include <string>
#include <tuple>
#include <vector>

#include "./util/lodepng.h"

#include "MapTypes.h"

namespace exportmaps_plugin
{

  typedef std::tuple<unsigned char, unsigned char, unsigned char> RGB_color;

  class ExportedMapBase
  {
  protected:
    std::vector<unsigned char>  image;
    std::string                 filename;
    int                         width;
    int                         height;
    MapType                     type;

  public:
    ExportedMapBase();

    ExportedMapBase(const std::string filename, int world_width, int world_height, MapType type);

    virtual void write_world_pixel (int pos_x,
                                    int pos_y,
                                    int px,
                                    int py,
                                    RGB_color& rgb) = 0;
    
    virtual void write_embark_pixel(int px,
                                    int py,
                                    RGB_color& rgb) = 0;

    virtual void write_thick_line_point(int px,
                                        int py,
                                        RGB_color& color_center,
                                        RGB_color& color_border) = 0;

    virtual void write_data(int pos_x,
                            int pos_y,
                            int px,
                            int py,
                            unsigned int value) = 0;

    virtual int write_to_disk() = 0;

	MapType get_type();
  };

  /*****************************************************************************
  *****************************************************************************/

  class ExportedMapDF : public ExportedMapBase
  {
	public:
		ExportedMapDF();
    ExportedMapDF(const std::string filename,
                  int world_width,
                  int world_height,
                  MapType type);

    void write_world_pixel(int pos_x,
                           int pos_y,
                           int px,
                           int py,
                           RGB_color& rgb);

    void write_embark_pixel(int px,
                            int py,
                            RGB_color& rgb);

    void write_thick_line_point(int px,
                                int py,
                                RGB_color& color_center,
                                RGB_color& color_border);

    void write_data(int pos_x,
                    int pos_y,
                    int px,
                    int py,
                    unsigned int value);

		int write_to_disk();
  };

  /*****************************************************************************
  *****************************************************************************/

  class ExportedMapRaw : public ExportedMapBase
  {
	public:
		ExportedMapRaw();
    ExportedMapRaw(const std::string filename,
                   int world_width,
                   int world_height,
                   MapType type);

    void write_world_pixel(int pos_x,
                           int pos_y,
                           int px,
                           int py,
                           RGB_color& rgb);

    void write_embark_pixel(int px,
                            int py,
                            RGB_color& rgb);

    void write_data(int pos_x,
                    int pos_y,
                    int px,
                    int py,
                    unsigned int value);

		int write_to_disk();
  };

}

#endif  // EXPORTED_MAP_H
