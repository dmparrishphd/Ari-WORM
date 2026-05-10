#include "dims.h"

#include "static_assert.h"

#include <limits.h>

STATIC_ASSERT ( 0 < NCORE ) ;

STATIC_ASSERT ( CHAR_BIT  ==         8 ) ;

STATIC_ASSERT ( UCHAR_MAX ==       255 ) ;

STATIC_ASSERT ( SCHAR_MAX ==      +127 ) ;
STATIC_ASSERT ( SCHAR_MIN ==      -128 ) ;

#if CHAR_MIN
STATIC_ASSERT ( CHAR_MAX  == SCHAR_MAX ) ;
STATIC_ASSERT ( CHAR_MIN  == SCHAR_MIN ) ;
#else
STATIC_ASSERT ( CHAR_MAX  == UCHAR_MAX ) ;
#endif

STATIC_ASSERT ( UCHAR_MAX  < INT_MAX   ) ;
STATIC_ASSERT ( SCHAR_MAX  < INT_MAX   ) ;
STATIC_ASSERT ( INT_MIN    < SCHAR_MIN ) ;
