#include "charsets.h"

#include "byte.h"
#include "dims.h"
#include "whitespace.h"

#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>

const char chr_noprint = '~' ;

const char chr_space   = '_' ;

#define N   ( 1 + UCHAR_MAX )

char prints [ N ] ;
        //  Any object of type byte is a valid
        //  index into prints.

char chr_print (
        const byte i )
{
    return prints [ i ] ;
}

char chr_graph (
        const byte i )
{
    return i == space ? chr_space : prints [ i ] ;
}

void charsets_reset ( void )
{
    static int defined = 0 ;
    if ( defined ) return ;
    assert ( isgraph ( chr_space ) ) ;
    assert ( isgraph ( chr_noprint ) ) ;
    const char s [ ] =
            " "
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "!\"#%&'()*+,-./:;<=>?[\\]^_{|}~" ;
    for ( int i = 0 ;  s [ i ] ;  ++ i )
    {
        assert (     0 < ( s [ i ] ) ) ;
        assert ( isprint ( s [ i ] ) ) ;
    }
    ( void ) memset ( prints , chr_noprint , N ) ;
    byte u ;
    for ( int i = 0 ;  ( u = s [ i ] ) ;  ++ i )
            prints [ u ] = u ;
    defined = 1 ;
}

#undef N
