#include "estream_puts.h"

#include "estream.h"

#include <assert.h>
#include <stddef.h>

void estream_puts (
        const char * const s )
{
    if ( ! s ) return ;
    size_t i = 0 ;
    while ( s [ i ] )
    {
        estream_putc ( s [ i ] ) ;
        //  Disallow wrap-around:---
        if ( ! ++ i ) return ;
    }
}
