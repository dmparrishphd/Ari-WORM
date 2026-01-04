#include "istream_scan.h"

#include "estream_alert.h"
#include "estream_display_hstr.h"
#include "estream_prompt.h"
#include "estream_put_bullet.h"
#include "estream_put_error.h"
#include "tri.h"
#include "hstr.h"
#include "hstr_clear.h"
#include "istream.h"
#include "istream_scrape.h"
#include "istream_skip.h"
#include "tracer.h"
#include "whitespace.h"

//  The type returned by the fetch function: tokens
//  that tell why the fetch function completes.
enum n_fetch
{
    overflow , // number of characters read exceeds allocation
    eof ,      // end-of-file
    eol ,      // end-of-line
    error ,    // file error
} ;

typedef
enum n_fetch
t_fetch ;



/*  The fetch function attempts to read a complete
 *  line by repeated calls to istream_scrape. The
 *  fetch function returns a value that indicates
 *  the reason for completing.
 *    The initial element of the array indicated by
 *  #0 stores the number of characters read.
 *    The array indicated by #1 stores the
 *  characters read, except end-of-line indicators.
 */
static
t_fetch fetch (
        size_t n [ static 1 ] ,
        char   h [ static HSTR_SIZE_MAX ] )
{
    TRACER_DECLARE ;
    hstr_clear ( h ) ;
    estream_prompt ( ) ;
    for ( * n = 0 ;  * n  <  HSTR_SIZE_MAX ;  ++ * n )
    {
        char c ;
        int code = istream_scrape ( & c ) ;
        if ( 0 < code ) return
                estream_put_error (
                    TRACER , "in istream_scrape" ) ,
                error ;
        if ( code < 0 )
        {
            if ( * h )
                    estream_put_bullet ( -1 ,
                            "Ignoring input:---" ) ,
                    estream_display_hstr ( h ) ;
            else
                    ( void ) estream_put_bullet ( -1 ,
                            "No input." ) ;
            hstr_clear ( h ) ;
            return eof ;
        }
        if ( c == newline ) return eol ;
        h [ * n ] = c ;
    }
    return
            estream_put_bullet (
                -1 , "Input rejected: long line." ) ,
            hstr_clear ( h ) ,
            overflow ;
}



int istream_scan (
        char h [ static HSTR_SIZE_MAX ] )
{
    TRACER_DECLARE ;
    size_t n = 0 ;
    switch ( fetch ( & n ,  h ) )
    {
        case eol   : return 0 ;
        case eof   : return -1 ;
        case error : return estream_alert (
            TRACER , "error in fetch" ) ;
        case overflow :
        {
            ( void ) estream_put_bullet (
                -1 , "Attempting to skip long line." ) ;
            TRI ( istream_skip ,  ISTREAM_SKIP_LIMIT - n ) ;
            return -1 ;
        }
        default    : return estream_alert (
            TRACER , "unrecognized token." ) ;
    }
}
