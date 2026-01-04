#include "istream_scrape.h"

#include "dims.h"
#include "char_from_uchar.h"
#include "istream_pop.h"

#include <assert.h>
#include <limits.h>

const int istream_scrape (
        char c [ static 1 ] )
{
    int i = -1 ;
    int code = istream_pop ( & i ) ;
    if ( code ) return code ;
    assert ( 0 <= i  &&  i <= UCHAR_MAX ) ;
    c [ 0 ] = char_from_uchar ( i ) ;   //NOTE [1]
    return 0 ;
}

/*  NOTES
 *
 *  NOTE [1] a character read by getchar is read
 *  as an unsigned-char--value. See N2176
 *      -   7.21.7.6 "The getchar function,"
 *      -   7.21.7.5 "The getc function," and
 *      -   7.21.7.1 "The fgetc function."
 *
 */
