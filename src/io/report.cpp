/*
 *		report.cpp - error/debug logging (reporting) module
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

#include "report.hpp"
#include <fstream>

std::ofstream logfile("arkilloid.log");
void log(std::string message)
{
	report(message, MSG_UNDEF);
}

void report(std::string message, int msgtype)
{
	switch(msgtype)
	{
		case MSG_DEBUG:
			#ifdef DEBUG
				logfile << "DEBUG: " << message << std::endl;
			#endif
			break;
		case MSG_ERROR:
			logfile << "ERROR: " << message << std::endl;
			break;
		case MSG_UNDEF:
			logfile << message << std::endl;
			break;
	}	
	logfile.flush();
}
