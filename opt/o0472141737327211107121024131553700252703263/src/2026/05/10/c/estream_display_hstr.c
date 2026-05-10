#include "estream_display_hstr.h"

#include "estream.h"
#include "estream_put_hstr.h"

void estream_display_hstr (
        const char h [ static HSTR_SIZE_MAX ] )
{
    if ( h  &&  h [ 0 ] )
            estream_endline  (   ) ,
            estream_put_hstr ( h ) ,
            estream_endline  (   ) ;
    else
            estream_put_blank_line ( ) ;
}
