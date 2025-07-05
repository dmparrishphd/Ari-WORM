#include "estream_put_msg.h"

#include "estream.h"
#include "estream_put_diagnostic.h"
#include "estream_puts.h"

#include <assert.h>



const char * const type [ ] =
{
    "WARNING" , // -1 --> 0
    "NOTE"    , //  0 --> 1
    "ERROR"   , // +1 --> 2
} ;



void estream_put_msg (
        const int          itp ,
        const char * const fil ,
        const char * const lin ,
        const char * const fun ,
        const char * const msg )
{
    int i = 1 + ( itp < 0 ? -1 : itp ? 1 : 0 ) ;
    estream_endline ( ) ;
    estream_puts ( type [ i ] )  ;
    estream_putc ( ':' ) ;
    estream_put_diagnostic ( fil , lin , fun ) ;
    estream_putc ( ':' ) ;
    estream_puts ( msg ) ;
    estream_endline ( ) ;
}
