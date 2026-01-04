#include "estream_put_msg.h"

#include "estream.h"
#include "estream_puts.h"

#include <assert.h>

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
    estream_endline ( ) ;
    estream_wrap ( ) ;
    estream_puts (
        ( 0 < typ ) ? ESTREAM_KW_ERROR   :
        ( typ < 0 ) ? ESTREAM_KW_WARNING :
                      ESTREAM_KW_NOTE    ) ;
    estream_puts (
        ( 0 < typ ) ? " at " : " re " ) ;
    estream_puts ( file + 2 ) ;
    estream_putx ( ) ;
    estream_puts ( trc -> line ) ;
    estream_puts ( " in " ) ;
    estream_puts ( trc -> func ) ;
    estream_puts ( " :---" ) ;
    estream_wrap ( ) ;
    estream_puts ( msg ) ;
    estream_endline ( ) ;
}
