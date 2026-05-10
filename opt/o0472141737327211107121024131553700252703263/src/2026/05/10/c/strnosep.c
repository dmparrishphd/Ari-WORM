#include "strnosep.h"

#include <assert.h>
#include <stddef.h>

size_t strnosep (
        const char * const s )
{
    size_t i = 0 ;
    while ( s [ i ]  &&  s [ i ] == ' ' )
            assert ( ++ i ) ;
    return i ;
}
