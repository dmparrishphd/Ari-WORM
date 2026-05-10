#include "estream_put_bullet.h"

#include "estream.h"
#include "estream_puts.h"

int estream_put_bullet (
        const int itp ,
        const char * const msg )
{
    estream_endline ( ) ;
    const int j = itp < 0 ? -1 : itp ? +1 : 0 ;
    const char * const b = 
        j == +1  ?  ESTREAM_BULLET_ERROR   :
        j        ?  ESTREAM_BULLET_WARNING :
                    ESTREAM_BULLET_NOTE    ;
    estream_puts ( b ) ;
    estream_puts ( msg ) ;
    estream_endline ( ) ;
    return j ;
}
