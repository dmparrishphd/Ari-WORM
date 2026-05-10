#include "strsep.h"
#include "strnosep.h"

#include <stddef.h>

void parse (
        size_t r [ static 2 ] ,
        const char * const s )
{
    r [ 0 ] = strnosep ( s ) ;
    r [ 1 ] = r [ 0 ] + strsep ( s + r [ 0 ] ) ;
}
