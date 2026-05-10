#include "estream_dump_hstr.h"

#include "charsets.h"
#include "estream_dump_byte.h"
#include "hstr.h"
#include "hstr_length.h"

void estream_dump_hstr (
        const char h [ static HSTR_SIZE_MAX ] )
{
    for ( int i = 0 ;  i < hstr_length ( h ) ;  ++ i )
            estream_dump_byte ( chr_noprint , h [ i ] ) ;
}
