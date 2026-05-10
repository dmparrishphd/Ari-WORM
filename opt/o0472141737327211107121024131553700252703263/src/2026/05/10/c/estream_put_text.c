#include "estream_put_text.h"

#include "estream.h"
#include "estream_put_wsep.h"
#include "parse.h"

#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>



static
const char * impress (
        const char * const s )
{
    size_t r [ 2 ] ;
    parse ( r , s ) ;
    if ( ! s [ r [ 0 ] ] )
            return NULL ;
    assert ( r [ 0 ] < r [ 1 ] ) ;
    estream_put_wsep ( r [ 1 ] - r [ 0 ] ) ;
    for ( size_t i = r [ 0 ] ;  i < r [ 1 ] ;  ++ i )
            estream_putc ( s [ i ] ) ;
    return s + r [ 1 ] ;
}



void estream_put_text (
        const char * const s )
{
    if ( ! s ) return ;
    const char * t = s ;
    while ( ( t = impress ( t ) ) ) ;
    return ;
}
