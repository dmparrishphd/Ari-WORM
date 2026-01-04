#include "istream_fetch.h"

#include "estream_alert.h"
#include "go.h"
#include "hstr.h"
#include "istream.h"
#include "istream_read.h"
#include "tracer.h"

int istream_fetch (
        char h [ static HSTR_SIZE_MAX ] )
{
    TRACER_DECLARE ;
    for ( int i = 0 ;  i < ISTREAM_HEIGHT ;  ++ i )
    {
        GO ( rejected , istream_read , h ) ;
        if ( rejected ) continue ;
        return 0 ;
    }
    return estream_alert ( TRACER ,
            " too many failed attempts at input." ) ;
}
