#include "estream_puts.h"

#include "estream.h"


// Minimum value of INT_MAX (N2176 5.2.4.2.1):---
#define M   ( 0x7fff )
#define H   ( ESTREAM_HEIGHT )
#define W   ( ESTREAM_WIDTH  )

#if M / W < H  ||  M / H < W
#define K   ( M )
#else
#define K   ( H * W )
#endif

void estream_puts (
        const char * const s )
{
    for ( unsigned i = 0 ;  s  &&  i < K  &&  s [ i ] ;  ++ i )
            estream_putc ( s [ i ] ) ;
}

#undef H
#undef K
#undef M
#undef W
