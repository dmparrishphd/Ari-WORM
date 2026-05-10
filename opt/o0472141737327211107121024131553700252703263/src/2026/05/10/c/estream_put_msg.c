#include "estream_put_msg.h"

#include "estream.h"
#include "estream_put_hstr.h"
#include "estream_put_text.h"
#include "estream_put_wsep.h"
#include "estream_puts.h"
#include "hstr.h"
#include "hstr_import.h"
#include "hstr_length.h"

#include <assert.h>

void put (
        const char * const s )
{
    assert ( s ) ;
    char h [ HSTR_SIZE_MAX ] ;
    assert ( ! hstr_import ( h , s ) ) ;
    estream_put_wsep ( hstr_length ( h ) ) ;
    estream_put_hstr ( h ) ;
}

void estream_put_msg (
        const int            typ ,
        const tracer * const trc ,
        const char   * const msg )
{
    assert ( trc ) ;
    const char * file = trc -> file ;
    assert (
            file &&
            file [ 0 ] == 'c' &&
            file [ 1 ] == '/' ) ;
    file += 2 ;
    estream_endline ( ) ;
    estream_put_blank_line ( ) ;
    put (
            ( 0 < typ ) ? ESTREAM_KW_ERROR   :
            ( typ < 0 ) ? ESTREAM_KW_WARNING :
                          ESTREAM_KW_NOTE    ) ;
    put ( ( 0 < typ ) ? "at" : "re" ) ;
    put ( file ) ;
    put ( trc -> line ) ;
    put ( "in" ) ;
    put ( trc -> func ) ;
    put ( ":---" ) ;
    estream_endline ( ) ;
    estream_put_text ( msg ) ;
    estream_endline ( ) ;
}
