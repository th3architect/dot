/*
* This file is part of DOT.
*
*     DOT is free software: you can redistribute it and/or modify
*     it under the terms of the GNU General Public License as published by
*     the Free Software Foundation, either version 3 of the License, or
*     (at your option) any later version.
*
*     DOT is distributed in the hope that it will be useful,
*     but WITHOUT ANY WARRANTY; without even the implied warranty of
*     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*     GNU General Public License for more details.
*
*     You should have received a copy of the GNU General Public License
*     along with DOT.  If not, see <http://www.gnu.org/licenses/>.
*
* Copyright 2011-2013 dothub.org
*/

/*
 * dot.cpp
 *
 *  Created on: 2013-03-18
 *      Author: Arup Raton Roy (ar3roy@uwaterloo.ca)
 */

#include <signal.h>
#include <cstring>
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>
#include "console/console.h"
#include "core/dotcore.h"

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;
using namespace console;
using namespace core;

int main(int argc, char* argv[])
{
    
   //initiate logging
    
   DOMConfigurator::configure("configurations/log/logConfig.xml");

   LoggerPtr rootLogger = Logger::getRootLogger();

   if(argc == 2 && strcmp(argv[1], "-d") == 0)
       rootLogger->setLevel(Level::getDebug());

        
    signal(SIGINT, Console::signalHandler);

    DOTCore::init();
    Console::start();
   
    return 0;
}