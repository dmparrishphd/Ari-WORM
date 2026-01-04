#include "istream_skim.h"

#include "estream_alert.h"
#include "go.h"
#include "hstr.h"
#include "hstr_clear.h"
#include "is_hstr_blank.h"
#include "istream.h"
#include "istream_scan.h"
#include "tracer.h"

#include <stdio.h>

int istream_skim (
        char h [ static HSTR_SIZE_MAX ] )
{
    TRACER_DECLARE ;
    _Static_assert ( 2 < ISTREAM_HEIGHT ,  "" ) ;
    for ( int i = 0 ;  i < ISTREAM_HEIGHT / 2 ;  ++ i )
    //  NOTE [1]
    {
        GO ( atypical , istream_scan , h ) ;
        if ( atypical ) clearerr ( stdin ) ;
        else if ( ! is_hstr_blank ( h ) ) return 0 ;
    }
    hstr_clear ( h ) ;
    return estream_alert ( TRACER , "too many empty lines." ) ;
}
/*  NOTE [1] Re "ISTREAM_HEIGHT / 2": One prompt and
 *  one user response are together at least 2 lines.
 *  If the user enters blank lines until the screen
 *  is filled with prompts and blank lines, the loop
 *  ends.
 */
