#ifndef H_DIMS
#define H_DIMS

#include <limits.h>

_Static_assert ( CHAR_BIT  ==    8 ,  "" ) ;

_Static_assert ( UCHAR_MAX ==  255 ,  "" ) ;

_Static_assert ( SCHAR_MAX == +127 ,  "" ) ;
_Static_assert ( SCHAR_MIN == -128 ,  "" ) ;

#if CHAR_MIN < 0
_Static_assert (  CHAR_MAX == +127 ,  "" ) ;
_Static_assert (  CHAR_MIN == -128 ,  "" ) ;
#else
_Static_assert (  CHAR_MAX ==  255 ,  "" ) ;
_Static_assert (  CHAR_MIN ==    0 ,  "" ) ;
#endif

/*  Given the above, and since the Standard
 *  guarantees
 *
 *      -   INT_MIN <= -32767 and
 *
 *      -   +32767 <= INT_MAX,
 *
 *  the following hold:
 *
 *      -   INT_MIN < UCHAR_MAX < INT_MAX
 *
 *      -   INT_MIN < SCHAR_MIN < INT_MAX
 *
 *      -   INT_MIN <  CHAR_MIN < INT_MAX
 */

#endif
