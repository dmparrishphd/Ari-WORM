#include "ari_proper.h"

#include "doatexit.h"
#include "hstr.h"
#include "istream_refetch.h"
#include "reset.h"
#include "tri.h"
#include "unittests.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TODO: move panel to its own file.
static
int panel ( void )
{
    TRACER_DECLARE ;
    char h [ HSTR_SIZE_MAX ] = { 0 } ;
    while ( ! 0 )
    {
        TRI ( istream_refetch , h ) ;
        //TODO: Do something with the characters read
    }
    return 0 ;
}



static
void cold ( void )
{
    ;
}



static
void warm ( void )
{
    clearerr ( stdin ) ;
}



static
int do_ari ( void )
{
    cold ( ) ;
    while ( ! 0 )
    {
        warm ( ) ;
        int code = panel ( ) ;
        if ( 0 < code ) exit ( EXIT_FAILURE ) ;
        if (   ! code ) exit ( EXIT_SUCCESS ) ;
    }
}



static
void dispatch_2 (
        const char * const s )
{
    #define CASE(t)   ( ! strcmp ( s , t ) )
    int ( * f ) ( void ) =
            CASE ( "--unittests" ) ? unittests :
            CASE ( "-t"          ) ? unittests :
         /* DEFAULT             */   NULL ;
    #undef CASE
    exit ( ( ! f  ||  f ( ) ) ? EXIT_FAILURE : EXIT_SUCCESS ) ;
}



static
void dispatch_n (
        int argc ,
        char * argv [ ] )
{
    exit ( EXIT_SUCCESS ) ;
}



int ari_proper (
        int argc ,
        char * argv [ ] )
{
    assert ( 0 < argc ) ;
    assert ( ! strcmp ( "ari" , argv [ 0 ] ) ) ;
    atexit ( doatexit ) ;
    reset ( ) ;
    /**/ if ( argc == 1 )
            do_ari ( ) ;
    else if ( argc == 2 )
            dispatch_2 ( argv [ 1 ] ) ;
    else //
            dispatch_n ( argc , argv ) ;
    assert ( ! "unreachable" ) ;
}
