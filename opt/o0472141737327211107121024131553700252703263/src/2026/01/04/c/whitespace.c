#include "whitespace.h"

#include <limits.h>

#define N   '\n'
#define S   ' '

_Static_assert ( 0 < N  &&  N <= CHAR_MAX ,  "" ) ;
_Static_assert ( 0 < S  &&  S <= CHAR_MAX ,  "" ) ;

const char newline = N ;
const char space   = S ;

#undef N
#undef S
