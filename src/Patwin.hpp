
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

#ifndef Patwin_h
#define Patwin_h

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <memory>
#include <boost/smart_ptr.hpp>
#include "Log.hpp"
#include "Config.hpp"

class Patwin
{
public:
    int run();
};

typedef boost::scoped_ptr<Patwin> PatwinServerObject;

#endif // Patwin_h
