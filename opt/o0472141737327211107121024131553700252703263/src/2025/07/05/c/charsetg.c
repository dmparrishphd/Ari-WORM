#include "charsetg.h"

#include "charset.h"
#include "charsetp.h"
#include "whitespace.h"

#include <ctype.h>
#include <assert.h>
#include <string.h>

#define N   ( CHARSET_SIZE )

const char charsetg_default = '_' ;

const char charsetg [ N ] ;

void charsetg_reset ( void )
{
    static int initialized = 0 ;
    if ( initialized ) return ;
    charsetp_reset ( ) ;
    assert ( isgraph ( charsetg_default ) ) ;
    memcpy ( ( void * ) charsetg ,  charsetp ,  N ) ;
    char * p = ( char * ) ( charsetg + space ) ;
    * p = charsetg_default ;
    for ( int i = 0 ;  charsetg [ i ] ;  ++ i )
            assert ( isgraph ( charsetg [ i ] ) ) ;
    initialized = 1 ;
}

#undef N
