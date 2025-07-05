#include "estream_put_note.h"

#include "estream_put_msg.h"

void estream_put_note (
        const char * const fil ,
        const char * const lin ,
        const char * const fun ,
        const char * const msg )
{
    estream_put_msg ( 0 , fil , lin , fun , msg ) ;
}
