#include "estream_put_note.h"

#include "estream_put_msg.h"
#include "tracer.h"

void estream_put_note (
        const tracer * const trc ,
        const char   * const msg )
{
    estream_put_msg ( 0 , trc , msg ) ;
}
