#include "charsetp.h"

#include "charset.h"
#include "prints.h"

#include <ctype.h>
#include <assert.h>
#include <string.h>

#define N   ( CHARSET_SIZE )

const char charsetp_default = '~' ;

const char charsetp [ N ] ;

void charsetp_reset ( void )
{
    static int initialized = 0 ;
    if ( initialized ) return ;
    assert ( isgraph ( charsetp_default ) ) ;
    const char set [ ] = PRINTS ;
    for ( int i = 0 ;  set [ i ] ;  ++ i )
            assert ( isprint ( set [ i ] ) ) ;
    char * p = ( char * ) charsetp ;
    memset ( p ,  charsetp_default ,  N - 1 ) ;
    p [ N - 1 ] = '\0' ;
    for ( int i = 0 ;  i < N ;  ++ i )
    {
        unsigned char u = set [ i ] ;
        assert ( u < CHARSET_NMEMB ) ;
        if ( ! u ) break ;
        p [ u ] = u ;
    }
    initialized = 1 ;
}

#undef N
