#include "estream_put_warning.h"

#include "estream_put_msg.h"

void estream_put_warning (
        const char * const fil ,
        const char * const lin ,
        const char * const fun ,
        const char * const msg )
{
    estream_put_msg ( -1 , fil , lin , fun , msg ) ;
}
