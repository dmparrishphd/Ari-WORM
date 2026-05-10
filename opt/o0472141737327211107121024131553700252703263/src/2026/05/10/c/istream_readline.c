#include "istream_readline.h"

#include "char_from_byte.h"
#include "estream_prompt.h"
#include "estream_put_error.h"
#include "estream_put_note.h"
#include "hstr_clear.h"
#include "is_hstr_blank.h"
#include "istream.h"
#include "tracer.h"
#include "whitespace.h"
#include "sighnd_int.h"
#include "static_assert.h"

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/*  The istream_readline function has been derived
 *  by simplifying the process formerly composed of:
 *
 *      -   istream_pop,
 *      -   istream_scrape,
 *      -   istream_skip,
 *      -   istream_scan,
 *      -   istream_skim,
 *      -   istream_read,
 *      -   istream_fetch, and
 *      -   istream_refetch
 */

static
void do_ferror (
        const tracer * const t )
{
    estream_put_error ( t , "file error in stdin" ) ;
    exit ( EXIT_FAILURE ) ;
}

static
void do_eof (
        const tracer * const t ,
        const int i )
{
    if ( i )
    {
        estream_put_error ( t , "unexpected end of file in stdin" ) ;
        exit ( EXIT_FAILURE ) ;
    }
    else
    {
        estream_put_note  ( t , "end of file in stdin" ) ;
        exit ( EXIT_SUCCESS ) ;
    }
}

static
void do_overflow (
        const tracer * const t )
{
    estream_put_error ( t , "overflow from stdin" ) ;
    exit ( EXIT_FAILURE ) ;
}

static
void end_or_error (
        const tracer * const t ,
        const int i )
{
    if ( istream_error ( )  &&  sigint_pending ( ) )
            sigint_respond (   ) ;
    else if ( istream_error ( ) ) do_ferror  ( t ) ;
    else if ( istream_eof   ( ) ) do_eof ( t , i ) ;
    else return ;
}

static
void istream_readline_inner (
        char h [ static HSTR_SIZE_MAX ] )
{
    TRACER_DECLARE ;
    hstr_clear ( h ) ;
    estream_prompt ( ) ;
    for ( int i = 0 ;  ;  ++ i )
    {
        end_or_error ( TRACER , i ) ; //NOTE [1]
        int c = getchar ( ) ;
        end_or_error ( TRACER , i ) ;
        if ( c == newline ) return ;
        if ( i == HSTR_INDEX_MAX ) do_overflow ( TRACER ) ;
        assert ( i < HSTR_INDEX_MAX ) ;
        assert ( 0 <= c  &&  c <= UCHAR_MAX ) ; //NOTE [2]
        h [ i ] = char_from_byte ( c ) ;
    }
    assert ( ! "unreachable" ) ;
}
/*  NOTE [1] During testing, found that getchar
 *  could return other than EOF even if the
 *  end-of-file indicator was set, contrary to
 *  description of getchar, getc, and fgetc.
 *
 *  NOTE [2] a character read by getchar is read
 *  as an unsigned-char--value. See N2176
 *      -   7.21.7.6 "The getchar function,"
 *      -   7.21.7.5 "The getc    function," and
 *      -   7.21.7.1 "The fgetc   function."
 */

void istream_readline (
        char h [ static HSTR_SIZE_MAX ] )
{
    TRACER_DECLARE ;
    for ( int i = 0 ;  i < ISTREAM_HEIGHT / 2 ;  ++ i ) //NOTE [1]
            if (
                istream_readline_inner ( h ) ,
                ! is_hstr_blank ( h ) )
                    return ;
    estream_put_error ( TRACER , "too many empty lines." ) ;
    exit ( EXIT_FAILURE ) ;
}
/*  NOTE [1] Re "ISTREAM_HEIGHT / 2": One prompt and
 *  one user response are together at least 2 lines.
 *  If the user enters blank lines until the screen
 *  is filled with prompts and blank lines (assuming
 *  input is echoed to the screen), the loop ends.
 */
