
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

#define RETURN_IF_FALSE( EXPR ) { if (! EXPR ) return false; }

#endif // Includes_h
