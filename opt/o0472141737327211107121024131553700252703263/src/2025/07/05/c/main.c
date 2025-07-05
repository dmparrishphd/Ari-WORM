#include "main.h"

#include "characters.h"
#include "doatexit.h"
#include "reset.h"
#include "unittests.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>



static
void dispatch0 (
        char * argv [ ] )
{
    exit ( EXIT_SUCCESS ) ;
}



static
void dispatch1 (
        char * argv [ ] )
{
    exit ( EXIT_SUCCESS ) ;
}



static
void dispatch2 (
        char * argv [ ] )
{
    assert ( argv [ 0 ] ) ;
    assert ( argv [ 1 ] ) ;
    const char * const a = argv [ 1 ] ;
    int ( * f ) ( void ) = NULL ;
         if ( ! strcmp ( a ,  "--unittests" ) ) f = unittests ;
    else if ( ! strcmp ( a ,           "-t" ) ) f = unittests ;
    else if ( ! strcmp ( a , "--characters" ) ) f = characters ;
    else ;
    if ( f ) assert ( ! f ( ) ) ;
    exit ( EXIT_SUCCESS ) ;
}



static
void dispatchn (
        char * argv [ ] )
{
    exit ( EXIT_SUCCESS ) ;
}



int main (
        int argc ,
        char * argv [ ] )
{
    atexit ( doatexit ) ;
    reset ( ) ;
         if ( argc <= 0 ) dispatch0 ( argv ) ;
    else if ( argc == 1 ) dispatch1 ( argv ) ;
    else if ( argc == 2 ) dispatch2 ( argv ) ;
    else                  dispatchn ( argv ) ;
    return 0 ;
}
