#ifndef H_GO
#define H_GO

#include "estream_alert.h"
#include "tracer.h"

#define GO(y,fn,...) \
        int y = 1 ; \
        { \
            y = fn ( __VA_ARGS__ ) ; \
            if ( 0 < y ) \
                    return estream_alert ( \
                        TRACER , "in " # fn "." ) ; \
            if ( y ) y = -1 ; \
        }

#endif
