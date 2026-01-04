#include "estream_put_hstr.h"

#include "estream.h"
#include "hstr.h"

#include <stddef.h>

void estream_put_hstr (
        const char h [ static HSTR_SIZE_MAX ] )
{
    size_t i = 0 ;
    while ( ( h [ i ] ) && ( i < HSTR_INDEX_MAX ) )
            estream_putc ( h [ i ++ ] ) ;
}
