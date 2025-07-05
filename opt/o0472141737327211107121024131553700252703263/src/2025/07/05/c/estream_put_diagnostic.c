#include "estream_put_diagnostic.h"

#include "estream.h"
#include "estream_puts.h"

void estream_put_diagnostic (
        const char * const fil ,
        const char * const lin ,
        const char * const fun )
{
    estream_puts ( fil ) ;
    estream_putc ( ':' ) ;
    estream_puts ( lin ) ;
    estream_putc ( ':' ) ;
    estream_puts ( fun ) ;
}
