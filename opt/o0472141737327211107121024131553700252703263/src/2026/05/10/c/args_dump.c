#include "args_dump.h"

#include "args.h"
#include "charsets.h"
#include "estream.h"
#include "estream_dump_hstr.h"
#include "estream_put_word.h"
#include "estream_put_wsep.h"
#include "hex.h"
#include "hstr_length.h"
#include "is_hstr.h"
#include "is_hstr_of_g.h"
#include "static_assert.h"
#include "whitespace.h"

#include <assert.h>
#include <limits.h>
#include <string.h>

static
void dump (
        const char h [ static HSTR_SIZE_MAX ] ,
        int i )
{
    STATIC_ASSERT ( HSTR_LEN_MAX < INT_MAX / 3 ) ;
    if ( i ) estream_put_wsep ( 3 * hstr_length ( h ) ) ;
    estream_dump_hstr ( h ) ;
}

int args_dump (
        const args * const a )
{
    assert ( a ) ;
    int n = args_nmemb ( a ) ;
    estream_endline ( ) ;
    for ( int i = 0 ;  i < n ;  ++ i )
    {
        char h [ HSTR_SIZE_MAX ] ;
        args_fetch ( h ,  a ,  i ) ;
        assert ( h [ 0 ] ) ;
        assert ( is_hstr ( h ) ) ;
        assert ( ! strchr ( h , space ) ) ;
        if ( is_hstr_of_g ( h ) && ! strchr ( h , chr_noprint ) )
                estream_put_word ( h ) ;
        else
                dump ( h , i ) ;
    }
    estream_endline ( ) ;
    return 0 ;
}
