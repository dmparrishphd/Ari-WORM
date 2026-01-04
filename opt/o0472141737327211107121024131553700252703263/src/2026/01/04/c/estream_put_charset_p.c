#include "estream_put_charset_p.h"

#include "estream.h"
#include "is_char_in_g.h"

#include <assert.h>
#include <ctype.h>
#include <limits.h>

typedef
int ( * const fun ) ( int ) ;

typedef
int ( * vfun ) ( int ) ;

fun const test [ ] =
{
    isupper ,
    islower ,
    isdigit ,
    ispunct ,
    NULL ,
} ;

#define W   ( ESTREAM_TEXT_WIDTH )
int estream_put_charset_p ( void )
{
    int i = 0 ;
    for ( vfun f = test [ i ] ;  f ;  f = test [ ++ i ] )
    {
        estream_wrap ( ) ;
        int k = 0 ; // characters written on the current line
        for ( int c = CHAR_MIN ;  c <= CHAR_MAX ;  ++ c )
        if ( is_char_in_g ( c )  &&  f ( c ) )
        {
            if ( estream_room ( ) < 2 )
                    k = 0 ,  estream_wrap ( ) ;
            if ( k ++ )
                    estream_putx ( ) ;
            else
                    assert ( W == estream_room ( ) ) ;
            estream_putc ( c ) ;
        }
    }
    return 0 ;
}
#undef W
