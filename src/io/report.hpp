/*
 *		report.cpp - error/debug logging (reporting) module headers
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

#ifndef REPORT_HPP_INCLUDED
#define REPORT_HPP_INCLUDED

#include <string>

enum msgtypes
{
	MSG_DEBUG,
	MSG_ERROR,
	MSG_UNDEF,
	MSG_WARN
};

void log(std::string message);
void report(std::string message, int msgtype);

#endif
