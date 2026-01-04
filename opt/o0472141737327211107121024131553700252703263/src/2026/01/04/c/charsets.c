#include "charsets.h"

#include "dims.h"

#include "whitespace.h"

#include <assert.h>
#include <ctype.h>
#include <string.h>

const char s = '_' ;
const char x = '~' ;

char map [ 1 + UCHAR_MAX ] ;
        //  Any object of type unsigned char is a valid
        //  index into map.

char chrp (
        const unsigned char i )
{
    return map [ i ] ;
}

char chrg (
        const unsigned char i )
{
    char c = chrp ( i ) ;
    return c == space ? s : c ;
}



void charsets_reset ( void )
{
    static int defined = 0 ;
    if ( defined ) return ;
    assert ( isgraph ( s ) ) ;
    assert ( isgraph ( x ) ) ;
    const char prints [ ] =
            " "
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "!\"#%&'()*+,-./:;<=>?[\\]^_{|}~" ;
    for ( int i = 0 ;  prints [ i ] ;  ++ i )
            assert ( isprint ( prints [ i ] ) ) ;
    for ( int i = 0 ;  i <= UCHAR_MAX ;  ++ i )
            map [ i ] = x ;
    unsigned char u ;
    for ( int i = 0 ;  ( u = prints [ i ] ) ;  ++ i )
            map [ u ] = u ;
    defined = 1 ;
}
