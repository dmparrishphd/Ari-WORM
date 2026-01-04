#include "istream_refetch.h"

#include "do.h"
#include "estream_display_hstr.h"
#include "estream_put_bullet.h"
#include "hstr.h"
#include "istream_fetch.h"
#include "tracer.h"

int istream_refetch (
        char h [ static HSTR_SIZE_MAX ] )
{
    TRACER_DECLARE ;
    DO ( istream_fetch , h ) ;
    estream_put_bullet ( 0 , "Received:---" ) ;
    estream_display_hstr ( h ) ;
    return 0 ;
}
