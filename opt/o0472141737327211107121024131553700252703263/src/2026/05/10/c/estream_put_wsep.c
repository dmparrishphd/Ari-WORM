#include "estream_put_wsep.h"

#include "estream.h"
#include "estream_pose.h"

#include <stddef.h>

static
void enough_room ( )
{
    if ( estream_pose ( ) ) estream_putx ( ) ;
}

static
void not_enough_room (
        const size_t k )
{
    if ( k <= ESTREAM_TEXT_WIDTH )
            estream_endline ( ) ;
    else
            estream_putx ( ) ;
}

void estream_put_wsep (
        const size_t k )
{
    if ( k < estream_room ( ) )
            enough_room ( ) ;
    else
            not_enough_room ( k ) ;
}
