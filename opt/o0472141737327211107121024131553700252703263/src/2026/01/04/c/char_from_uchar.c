#include "char_from_uchar.h"

#include <limits.h>

/*

    "When a value with integer type is converted to
    "another integer type other than _Bool, if the
    "value can be represented by the new type, it is
    "unchanged.
    "  Otherwise, if the new type is unsigned, the
    "value is converted by repeatedly adding or
    "subtracting one more than the maximum value
    "that can be represented in the new type until
    "the value is in the range of the new type"
    (N2176 6.3.1.3-1--6.3.1.3-1-2).

    Specifically:

    "When a value with [ char ] type is converted to
    "[ an unsigned char type ], if the value can be
    "represented by the [ unsigned char ] type, it
    "is unchanged.
    "  Otherwise... the value is converted by
    "repeatedly adding... one more than [ UCHAR_MAX ]
    "until the value is in the range of [ unsigned
    "char]."

    In converting from { unsigned char } to { char },
    we assume that the { unsigned char } value was
    the result of conversion from a { char } value.
    Therefore:

*/


#if CHAR_MIN

_Static_assert ( CHAR_MAX == SCHAR_MAX ,  "" ) ;
_Static_assert ( CHAR_MIN == SCHAR_MIN ,  "" ) ;
//  The smallest value to be converted is ( 1 + CHAR_MAX ).
//  The corresponding converted value is ( 1 + CHAR_MAX ) - ( UCHAR_MAX + 1 )
//  The converted value must be in range:---
_Static_assert ( CHAR_MIN <= ( 1 + CHAR_MAX ) - ( UCHAR_MAX + 1 ) , "" ) ;

const char char_from_uchar (
        const unsigned char u )
{
    return u <= CHAR_MAX ? u : u - ( UCHAR_MAX + 1 ) ;
}

#else // No conversion is necessary

_Static_assert ( CHAR_MAX == UCHAR_MAX ,  "" ) ;
_Static_assert ( CHAR_MIN ==         0 ,  "" ) ;

const char char_from_uchar (
        const unsigned char u )
{
    return u ;
}

#endif
