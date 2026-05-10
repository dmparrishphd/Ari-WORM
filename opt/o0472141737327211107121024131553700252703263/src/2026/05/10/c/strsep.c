#include "strsep.h"

#include <assert.h>
#include <stddef.h>

size_t strsep (
        const char * const s )
{
    size_t i = 0 ;
    while ( s [ i ]  &&  s [ i ] != ' ' )
            assert ( ++ i ) ;
    return i ;
}
