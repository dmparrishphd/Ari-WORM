#ifndef H_DO
#define H_DO

#include "estream_alert.h"
#include "tracer.h"

#define DO(fn,...) \
        if ( fn ( __VA_ARGS__ ) ) return \
                estream_alert ( TRACER , "in " # fn "." ) ; \
        else ;

#endif
