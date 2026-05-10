#include "estream_put_guide.h"

#include "estream.h"
#include "whitespace.h"

void estream_put_guide ( void )
{
    int r ;
    while ( ( r = estream_room ( ) ) )
            estream_putc ( ( r % 3 ) ? '_' : space ) ;
    estream_endline ( ) ;
}
