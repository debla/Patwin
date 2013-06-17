
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

#ifndef Includes_h
#define Includes_h

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif 

#include <stdint.h>

typedef int8_t     int8;
typedef int16_t   int16;
typedef int32_t   int32;
typedef int64_t   int64;

typedef uint8_t   uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef wchar_t wchar;

#define RETURN_IF_FALSE( EXPR ) \
    { if (! EXPR ) return false; }

#endif // Includes_h
