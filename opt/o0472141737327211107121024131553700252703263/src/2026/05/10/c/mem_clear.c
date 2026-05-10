#include "mem_clear.h"

#include <stddef.h>
#include <string.h>

void mem_clear (
        void * const s ,
        const size_t n )
{
    if ( s ) ( void ) memset ( ( void * ) s , 0 , n ) ;
}
