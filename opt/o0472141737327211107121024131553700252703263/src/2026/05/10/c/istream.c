#include "istream.h"

#include "static_assert.h"

#include <stdio.h>

STATIC_ASSERT ( 2 < ISTREAM_HEIGHT ) ;



int istream_error ( void )
{
    return ! ! ferror ( stdin ) ;
}



int istream_eof ( void )
{
    return ! ! feof ( stdin ) ;
}
