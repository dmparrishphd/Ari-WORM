#include "istream_pop.h"

#include "dims.h"
#include "estream_alert.h"
#include "estream.h"
#include "estream_put_bullet.h"
#include "istream.h"
#include "sighnd_int.h"
#include "tracer.h"

#include <assert.h>
#include <stdio.h>

static
int end_or_error (
        const tracer * const trc )
{
    if ( istream_error ( )  &&  sigint_pending ( ) ) return
            sigint_respond ( ) ,  -1 ;
    else if ( istream_error ( ) ) return
            estream_alert ( trc , "file error in stdin." ) ;
    else if ( istream_eof   ( ) ) return
            estream_put_gap ( ) ,
            estream_put_bullet ( -1 , "End-of-file in stdin." ) ;
    else return 0 ;
}

const int istream_pop (
        int i [ static 1 ] )
{
    TRACER_DECLARE ;
    int condition = 0 ;
    if ( ( condition = end_or_error ( TRACER ) ) )
            return condition ;  //NOTE [1]
    int j = getchar ( ) ;       //NOTE [2]
    if ( ( condition = end_or_error ( TRACER ) ) )
            return condition ;
    assert ( 0 <= j  &&  j <= UCHAR_MAX ) ; //NOTE [2]
    i [ 0 ] = j ;
    return 0 ;
}

/*  NOTES
 *
 *  NOTE [1] During testing, found that getchar
 *  could return other than EOF even if the
 *  end-of-file indicator was set, contrary to
 *  description of getchar, getc, and fgetc.
 *
 *  NOTE [2] a character read by getchar is read
 *  as an unsigned-char--value. See N2176
 *      -   7.21.7.6 "The getchar function,"
 *      -   7.21.7.5 "The getc function," and
 *      -   7.21.7.1 "The fgetc function."
 *
 */
