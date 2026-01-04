#include "estream_note.h"

#include "estream_put_note.h"
#include "tracer.h"

int estream_note (
        const tracer * const trc ,
        const char   * const msg )
{
    estream_put_note ( trc , msg ) ;
    return 0 ;
}
