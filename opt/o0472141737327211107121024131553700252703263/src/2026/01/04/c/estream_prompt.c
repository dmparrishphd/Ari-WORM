#include "estream_prompt.h"

#include "estream.h"
#include "hstr.h"
#include "whitespace.h"

#include <stdio.h>

// ASSUME THAT stderr AND stdin ARE CONNECTED TO
// THE SAME INTERACTIVE DEVICE.
void estream_prompt ( void )
{
    estream_endline ( ) ;
    for ( int i = 0 ;  i < HSTR_LEN_MAX ;  ++ i )
            estream_putc ( '_' ) ;
    estream_endline ( ) ;
    for ( int i = 0 ;  i < ESTREAM_MARGIN_LEFT ;  ++ i )
        fputc ( space , stderr ) ;
}
