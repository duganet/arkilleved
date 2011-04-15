/*
 *		file.cpp - file module
 *
 *		Copyright 2010 Maxim Kachur <mcdebugger@duganet.ru>
 *		Copyright 2010 Sergey Babneev <plughead@mail.ru>
 *		
 *		This file is part of Arkilloid.
 *
 *		Arkilloid is free software: you can redistribute it and/or modify
 *		it under the terms of the GNU General Public License as published by
 *		the Free Software Foundation, either version 3 of the License, or
 *		(at your option) any later version.
 *
 *		Arkilloid is distributed in the hope that it will be useful,
 *		but WITHOUT ANY WARRANTY; without even the implied warranty of
 *		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *		GNU General Public License for more details.
 *
 *		You should have received a copy of the GNU General Public License
 *		along with Arkilloid.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "file.hpp"

std::string path_construct(std::string dir_shortname, std::string filename)
{
    std::string dir_basename;
    #ifdef _WIN32
		dir_basename = ".";
    #else
		#ifdef DATAROOTDIR
			dir_basename = DATAROOTDIR "/" PACKAGE;
		#else
			dir_basename = DATADIR;
		#endif
    #endif
    return dir_basename + '/' + dir_shortname + "/" + filename;
}
