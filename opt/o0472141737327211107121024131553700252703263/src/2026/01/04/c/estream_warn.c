#include "estream_warn.h"

#include "estream_put_warning.h"
#include "tracer.h"

int estream_warn (
        const tracer * const trc ,
        const char   * const msg )
{
    estream_put_warning ( trc , msg ) ;
    return -1 ;
}
