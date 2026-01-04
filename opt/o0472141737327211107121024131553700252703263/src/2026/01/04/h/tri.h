#ifndef H_TRI
#define H_TRI

#include "estream_alert.h"
#include "tracer.h"

#define CODE urn_uuid_0e51cff9_c46d_47c5_8565_bcb494f96ad2
#define TRI(fn,...)                              \
{                                                \
    const int CODE = fn ( __VA_ARGS__ ) ;        \
    if ( CODE < 0 ) return -1 ;                  \
    if ( 0 < CODE ) return estream_alert (       \
                    TRACER , "in " # fn "." ) ; \
}
#undef CODE

#endif
