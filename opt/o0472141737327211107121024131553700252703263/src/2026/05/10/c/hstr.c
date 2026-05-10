#include "hstr.h"

#include "estream.h"
#include "static_assert.h"

#include <limits.h>

#define I   ( HSTR_INDEX_MAX )
#define L   ( HSTR_LEN_MAX )
#define N   ( HSTR_SIZE_MAX )

STATIC_ASSERT ( 0 < N  &&  N < INT_MAX ) ;

STATIC_ASSERT ( I == N - 1 ) ;
STATIC_ASSERT ( 0 <= I  &&  I <= UCHAR_MAX ) ;

STATIC_ASSERT ( L == I ) ;
STATIC_ASSERT ( L <= ESTREAM_TEXT_WIDTH ) ;

#undef I
#undef L
#undef N
