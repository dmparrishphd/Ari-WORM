#include "uuid4.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NB   (     18 ) // Number of random bytes
#define NY   ( 2 * NB ) // Number of random nybls

/*  Indices of characters of canonical form of UUID
 *            1         2         3
 *  0123456789012345678901234567890123456
 *  xxxxxxxx-xxxx-Mxxx-Nxxx-xxxxxxxxxxxx0
 */

static
int doError (
        const char * const s )
{
    fprintf ( stderr ,  "%s\n" , s ) ;
    exit ( EXIT_FAILURE ) ;
}



int uuid4 ( void )
{
    unsigned char a [ NY + 1 ] ;

    //  Read NB elements into the initial NB elements of { a }.
    {
        #define RANDOM_FILE   "/dev/urandom"
        FILE * f = fopen ( RANDOM_FILE , "rb" ) ;
        if ( ! f ) doError ( "could not open " RANDOM_FILE ) ;
        int n = fread ( a , 1 , NB , f ) ;
        if ( n != NB ) doError (
                    "could not read enough bytes from " RANDOM_FILE ) ;
        if ( fclose ( f ) ) doError (
                    "could not close" RANDOM_FILE ) ;
        #undef RANDOM_FILE
    }

    //  Keep only the lower 8 bits of each member of
    //  { a }.  Redistribute the nybls from the initial
    //  NB elments of { a } to the initial NY elements
    //  of { a }. Since the nybls are random, their
    //  order is not significant.
    memcpy ( a + NB ,  a ,  NB ) ;
    for ( int i = 0 ;  i < NB ;  ++ i )
            a [ i ] = a [ i ] >> 4 ;
    for ( int i = 0 ;  i < NY ;  ++ i )
            a [ i ] = a [ i ] & 0x0f ;

    a [ 14 ] = 4 ;  // Set version
    a [ 19 ] &= 0x03 ;  a [ 19 ] |= 0x08 ;  // Set variant

    //  Compute the canonical form of a UUID represented
    //  in { a }.
    char h [ NY + 1 ] ;
    for ( int i = 0 ;  i < NY ;  ++ i )
            h [ i ] = "0123456789abcdef" [ a [ i ] ] ;
    for ( int i = 8 ;  i < 24 ;  i += 5 )
            h [ i ] = '-' ;
    h [ NY ] = '\0' ;

    if ( puts ( h ) < 0 ) doError (
            "could not write to stdandard output." ) ;

    exit ( EXIT_SUCCESS ) ;
}

#undef NB
#undef NY
