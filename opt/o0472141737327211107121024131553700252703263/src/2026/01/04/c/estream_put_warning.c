#include "estream_put_warning.h"

#include "estream_put_msg.h"
#include "tracer.h"

void estream_put_warning (
        const tracer * const trc ,
        const char   * const msg )
{
    estream_put_msg ( -1 , trc , msg ) ;
}
