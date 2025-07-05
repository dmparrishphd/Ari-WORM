#include "reset.h"

#include "charsetg.h"
#include "charsetp.h"
#include "estream.h"

#include <assert.h>

void reset ( void )
{
    charsetp_reset ( ) ;
    charsetg_reset ( ) ;
    estream_reset ( ) ;
}
