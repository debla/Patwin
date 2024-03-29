
/*
    Copyright (C) 2013 Denis Blank

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Config.hpp"
#include "Log.hpp"
#include "Patwin.hpp"

int main(int argc, char* argv[])
{
    sLog.outInfo("Patwin - (c) 2013 Denis Blank");
    if (!sConfig.Load(argc, argv))
        return EXIT_FAILURE;

    PatwinServerObject patwin(new Patwin());
    return patwin->run();
}
