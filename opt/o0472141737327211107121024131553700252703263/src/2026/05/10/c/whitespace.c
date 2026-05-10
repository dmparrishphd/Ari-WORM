#include "whitespace.h"

#include <limits.h>

#include "static_assert.h"

#define N   '\n'
#define S   ' '

STATIC_ASSERT ( 0 < N  &&  N <= CHAR_MAX ) ;
STATIC_ASSERT ( 0 < S  &&  S <= CHAR_MAX ) ;

const char newline = N ;
const char space   = S ;

#undef N
#undef S
