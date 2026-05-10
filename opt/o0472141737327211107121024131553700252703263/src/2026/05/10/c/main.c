#include "main.h"

#include "ari_improper.h"
#include "ari_proper.h"
#include "tracer.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

int main (
        int argc ,
        char * argv [ ] )
{
    if ( argc < 1 ) exit ( EXIT_FAILURE ) ;
    if ( strcmp ( "ari" , argv [ 0 ] ) )
            ari_improper ( argc , argv ) ;
    else
            ari_proper ( argc , argv ) ;
    assert ( ! "unreachable" ) ;
}
