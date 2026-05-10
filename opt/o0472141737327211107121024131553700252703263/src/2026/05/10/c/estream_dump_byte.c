#include "estream_dump_byte.h"

#include "byte.h"
#include "estream.h"
#include "estream_put_wsep.h"
#include "hex.h"

void estream_dump_byte (
        const char x ,
        const byte u )
{
    if ( estream_room ( ) < ( 2 + ! ! x ) )
            estream_wrap ( ) ;
    if ( x )
            estream_putc ( x ) ;
    estream_putc ( hex_hi ( u ) ) ;
    estream_putc ( hex_lo ( u ) ) ;
}
