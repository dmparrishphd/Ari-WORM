#include "estream_put_hstr.h"

#include "estream.h"
#include "hstr.h"

void estream_put_hstr (
        const char h [ static HSTR_SIZE_MAX ] )
{
    for ( int i = 0 ;   h [ i ]  &&  i < HSTR_INDEX_MAX ;   ++ i )
            estream_putc ( h [ i ] ) ;
}
