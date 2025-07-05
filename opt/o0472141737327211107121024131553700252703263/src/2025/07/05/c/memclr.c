#include "memclr.h"

#include <stddef.h>
#include <string.h>

void memclr (
        void * const s ,
        const size_t n )
{
    if ( s ) ( void ) memset ( ( void * ) s , 0 , n ) ;
}
