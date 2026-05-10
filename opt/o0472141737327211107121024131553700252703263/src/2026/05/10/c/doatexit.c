#include "doatexit.h"

#include "ari.h"
#include "estream.h"

void doatexit ( void )
{
    //TODO: attempt to save definitions, etc.
    estream_flush ( ) ;
    mari_unset ( ) ;
}
