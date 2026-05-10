#include "hstr_copy.h"

#include "estream_alert.h"
#include "hstr.h"
#include "tracer.h"

#include <assert.h>
#include <string.h>

#define N   ( HSTR_SIZE_MAX  )
#define M   ( HSTR_INDEX_MAX )

int hstr_copy (
              char t [ static N ] ,
        const char s [ static N ] )
{
    TRACER_DECLARE ;
    char c [ N ] ; //NOTE [1]
    ( void ) memcpy  ( c , s , N ) ; //NOTE [1]
    ( void ) strncpy ( t , c , N ) ; //NOTE [2]
    if ( memcmp ( c , s , N ) )
            return estream_alert (
                TRACER , "overlap detected." ) ;
    int r = t [ M ] ? -1 : 0 ;
    t [ M ] = '\0' ;
    return r ;
}
/*  NOTES
 *
 *      [1] Make a copy of the source array that is
 *          guaranteed not to overlap with the source
 *          array.
 *
 *      [2] Copy between objects that are guaranteed not
 *          to overlap because "if copying takes place between
 *          objects that overlap, the behavior is undefined"
 *          (N2176 7.24.2.4).
 */

#undef N
