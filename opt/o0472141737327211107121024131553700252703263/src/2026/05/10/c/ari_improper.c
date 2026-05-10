#include "ari_improper.h"

#include "uuid4.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ari_improper (
        int argc ,
        char * argv [ ] )
{
    assert ( 0 < argc ) ;
    const char * const command = argv [ 0 ] ;
    assert ( strcmp ( "ari" , command ) ) ;
    if ( ! strcmp ( "uuid4" ,  command ) )
    {
            uuid4 ( ) ;
    }
    else
    {
        fprintf ( stderr , "unrecognized command\n" ) ;
        exit ( EXIT_FAILURE ) ;
    }
    assert ( ! "unreachable" ) ;
}
