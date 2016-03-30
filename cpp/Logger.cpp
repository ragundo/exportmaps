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

#include <iomanip>
#include "../include/Logger.h"


Logger::Logger(DFHack::color_ostream& out) : _out(out) {};

void Logger::log(std::string st)
{
  _out << st;
}

void Logger::log_line(std::string st)
{
  _out << st << std::endl;
}

void Logger::log_endl()
{
  _out << std::endl;
}

void Logger::log_cr()
{
  _out << "\r" << std::flush;
}

void Logger::log_number(unsigned int i)
{
  _out << i;
}

void Logger::log_number(unsigned int i, unsigned int width)
{
  _out << std::setw(width) << i;
}