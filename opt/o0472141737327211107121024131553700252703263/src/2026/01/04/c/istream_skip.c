#include "istream_skip.h"

#include "estream_alert.h"
#include "estream_put_bullet.h"
#include "istream.h"
#include "istream_pop.h"
#include "tracer.h"
#include "whitespace.h"

#include <stddef.h>
#include <stdio.h>

//DESIGN:---
/*  -   Lines of input short enough to fit into a short
 *      string shall not be skipped and
 *  -   The value of ISTREAM_SKIP_LIMIT shall be
 *      representable by an object of type size_t.
 */
_Static_assert (
    HSTR_SIZE_MAX <= ISTREAM_SKIP_LIMIT  &&
    ISTREAM_SKIP_LIMIT <= SIZE_MAX ,  "" ) ;

static
int with_effect (
        const int code )
{
    if ( ! code ) ( void ) estream_put_bullet (
        -1 , "Long line skipped." ) ;
    return code ;
}

int istream_skip (
        const size_t n )
{
    TRACER_DECLARE ;
    int k = 0 ;
    int code = 0 ;
    for ( size_t i = 0 ;  i < n ;  ++ i ) if (
        ( code = istream_pop ( & k ) ) || ( k == newline ) )
            return with_effect ( code ) ;
    return estream_alert ( TRACER , "End-of-line not found." ) ;
}
