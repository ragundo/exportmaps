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

#include <math.h>
#include "../include/ExportedMap.h"

using namespace exportmaps_plugin;

ExportedMapBase::ExportedMapBase()
{
}

ExportedMapBase::ExportedMapBase(const std::string filename, int world_width, int world_height, MapType type)
	  : filename(filename), 
    width(world_width*16), 
    height(world_height*16), 
    type(type)
{
}

MapType ExportedMapBase::get_type()
{
	return type;
}

//////////////////////////////////////////

ExportedMapDF::ExportedMapDF()
{
}

ExportedMapDF::ExportedMapDF(const std::string filename, int world_width, int world_height, MapType type)
	: ExportedMapBase(filename,world_width,world_height,type)
{
    // Each world tile has 16 * 16 pixels. Each pixel needs 4 bytes
    image.resize(world_width * world_height * 16 * 16 * 4); // 4 = RGBA for PNG
}

void ExportedMapDF::write_world_pixel(int pos_x, int pos_y, int px, int py, std::tuple<unsigned char, unsigned char, unsigned char>& rgb)
{
    int index_png = pos_y * 16 * height +
                    pos_x * 16          +
                    py         * height +
                    px;

    image[4*index_png + 0] = std::get<0>(rgb);
    image[4*index_png + 1] = std::get<1>(rgb);
    image[4*index_png + 2] = std::get<2>(rgb);
    image[4*index_png + 3] = 255;    // Solid color
}

void ExportedMapDF::write_embark_pixel(int px, int py, std::tuple<unsigned char, unsigned char, unsigned char>& rgb) 
{
    int dpy = py >> 4;
    int dpx = px >> 4;
    int mpy = py % 16;
    int mpx = px % 16;

    int index_png = dpy * 16 * height +
                    dpx * 16          +
                    mpy      * height +
                    mpx;

    image[4*index_png + 0] = std::get<0>(rgb);
    image[4*index_png + 1] = std::get<1>(rgb);
    image[4*index_png + 2] = std::get<2>(rgb);
    image[4*index_png + 3] = 255;    // Solid color    
}

void ExportedMapDF::write_thick_line_point(int px, 
                                           int py, 
                                           std::tuple<unsigned char, unsigned char, unsigned char>& color_center,
                                           std::tuple<unsigned char, unsigned char, unsigned char>& color_border) 
{
    int dpy = py >> 4;
    int dpx = px >> 4;
    int mpy = py % 16;
    int mpx = px % 16;

    int index_png = dpy * 16 * height +
                    dpx * 16          +
                    mpy      * height +
                    mpx;    

    unsigned char r_center = std::get<0>(color_center);
    unsigned char g_center = std::get<1>(color_center);
    unsigned char b_center = std::get<2>(color_center);


    image[4*index_png + 0] = r_center;
    image[4*index_png + 1] = g_center;
    image[4*index_png + 2] = b_center;
    image[4*index_png + 3] = 255;    // Solid color  

    unsigned char r_border = std::get<0>(color_border);
    unsigned char g_border = std::get<1>(color_border);
    unsigned char b_border = std::get<2>(color_border);

    if (!((image[4*index_png + 4 + 0] == r_center) &&
          (image[4*index_png + 4 + 1] == g_center) && 
          (image[4*index_png + 4 + 2] == b_center)
         )
       ) 
    {
      image[4*index_png + 4 + 0] = r_border;
      image[4*index_png + 4 + 1] = g_border;
      image[4*index_png + 4 + 2] = b_border;
      image[4*index_png + 4 + 3] = 255;    // Solid color  
    }

    if (!((image[4*index_png - 4 + 0] == r_center) &&
          (image[4*index_png - 4 + 1] == g_center) && 
          (image[4*index_png - 4 + 2] == b_center)
         )
       ) 
    {
      image[4*index_png - 4 + 0] = r_border;
      image[4*index_png - 4 + 1] = g_border;
      image[4*index_png - 4 + 2] = b_border;
      image[4*index_png - 4 + 3] = 255;    // Solid color  
    }    

    index_png -= this->width;

    if (!((image[4*index_png + 4 + 0] == r_center) &&
          (image[4*index_png + 4 + 1] == g_center) && 
          (image[4*index_png + 4 + 2] == b_center)
         )
       ) 
    {
      image[4*index_png + 4 + 0] = r_border;
      image[4*index_png + 4 + 1] = g_border;
      image[4*index_png + 4 + 2] = b_border;
      image[4*index_png + 4 + 3] = 255;    // Solid color  
    }

    if (!((image[4*index_png + 0 + 0] == r_center) &&
          (image[4*index_png + 0 + 1] == g_center) && 
          (image[4*index_png + 0 + 2] == b_center)
         )
       ) 
    {
      image[4*index_png + 0 + 0] = r_border;
      image[4*index_png + 0 + 1] = g_border;
      image[4*index_png + 0 + 2] = b_border;
      image[4*index_png + 0 + 3] = 255;    // Solid color  
    }

    if (!((image[4*index_png - 4 + 0] == r_center) &&
          (image[4*index_png - 4 + 1] == g_center) && 
          (image[4*index_png - 4 + 2] == b_center)
         )
       ) 
    {
      image[4*index_png - 4 + 0] = r_border;
      image[4*index_png - 4 + 1] = g_border;
      image[4*index_png - 4 + 2] = b_border;
      image[4*index_png - 4 + 3] = 255;    // Solid color  
    }    


    index_png += this->width * 2;

    if (!((image[4*index_png + 4 + 0] == r_center) &&
          (image[4*index_png + 4 + 1] == g_center) && 
          (image[4*index_png + 4 + 2] == b_center)
         )
       ) 
    {
      image[4*index_png + 4 + 0] = r_border;
      image[4*index_png + 4 + 1] = g_border;
      image[4*index_png + 4 + 2] = b_border;
      image[4*index_png + 4 + 3] = 255;    // Solid color  
    }

    if (!((image[4*index_png + 0 + 0] == r_center) &&
          (image[4*index_png + 0 + 1] == g_center) && 
          (image[4*index_png + 0 + 2] == b_center)
         )
       ) 
    {
      image[4*index_png + 0 + 0] = r_border;
      image[4*index_png + 0 + 1] = g_border;
      image[4*index_png + 0 + 2] = b_border;
      image[4*index_png + 0 + 3] = 255;    // Solid color  
    }

    if (!((image[4*index_png - 4 + 0] == r_center) &&
          (image[4*index_png - 4 + 1] == g_center) && 
          (image[4*index_png - 4 + 2] == b_center)
         )
       ) 
    {
      image[4*index_png - 4 + 0] = r_border;
      image[4*index_png - 4 + 1] = g_border;
      image[4*index_png - 4 + 2] = b_border;
      image[4*index_png - 4 + 3] = 255;    // Solid color  
    }  




}


void ExportedMapDF::write_data(int pos_x, int pos_y, int px, int py, unsigned int value)
{
}


int ExportedMapDF::write_to_disk()
{
    //Encode from raw pixels to disk with a single function call
    //The image argument has width * height RGBA pixels or width * height * 4 bytes
    return lodepng::encode(filename, image, width, height);
}



//////////////////////////////////////////

ExportedMapRaw::ExportedMapRaw()
{
}

ExportedMapRaw::ExportedMapRaw(const std::string filename, int world_width, int world_height, MapType type)
	: ExportedMapBase(filename,world_width,world_height,type)
{
    // Each world tile has 16 * 16 entries. Each entry needs 2 bytes
    image.resize(world_width * world_height * 16 * 16 * 2);
}

void ExportedMapRaw::write_world_pixel(int pos_x, int pos_y, int px, int py, std::tuple<unsigned char, unsigned char, unsigned char>& rgb)
{

}

void ExportedMapRaw::write_embark_pixel(int px, int py, std::tuple<unsigned char, unsigned char, unsigned char>& rgb) 
{
}

void ExportedMapRaw::write_data(int pos_x, int pos_y, int px, int py, unsigned int value)
{
    int index_buffer = pos_y * 16 * height +
                       pos_x * 16          +
                       py         * height  +
                       px;

	float f = (float)value/256;

    image[2*index_buffer + 0] = (value <= 255 ? value : value % 256);
    image[2*index_buffer + 1] = (value <= 255 ? 0     : (unsigned int)floor(f));
}


int ExportedMapRaw::write_to_disk()
{
	// Write the buffer to the fstream
	// TODO
    return 0;
}



