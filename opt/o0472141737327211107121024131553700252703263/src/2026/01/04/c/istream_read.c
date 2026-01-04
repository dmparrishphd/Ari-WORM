#include "istream_read.h"

#include "estream_put_bullet.h"
#include "go.h"
#include "is_hstr_of_p.h"
#include "istream_skim.h"
#include "tracer.h"

int istream_read (
    char h [ static HSTR_SIZE_MAX ] )
{
    TRACER_DECLARE ;
    GO ( rejected , istream_skim , h ) ;
    if ( rejected ) return estream_put_bullet ( -1 ,
            "Input rejected by istream_skim." ) ;
    if ( is_hstr_of_p ( h ) ) return 0 ;
    return estream_put_bullet ( -1 ,
            "Input rejected: unrecognized character(s) found." ) ;
}
