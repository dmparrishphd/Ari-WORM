#include "estream_put_error.h"

#include "estream_put_msg.h"

void estream_put_error (
        const tracer * const trc ,
        const char   * const msg )
{
    estream_put_msg ( 1 , trc , msg ) ;
}
