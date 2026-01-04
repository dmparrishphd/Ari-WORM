#include "estream_alert.h"

#include "estream_put_error.h"

int estream_alert (
        const tracer * const trc ,
        const char   * const msg )
{
    estream_put_error ( trc , msg ) ;
    return 1 ;
}
