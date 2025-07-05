#include "characters.h"

#include "estream.h"
#include "uppers.h"
#include "lowers.h"
#include "digits.h"
#include "puncts.h"

#include <stddef.h>

void put (
        const char * const s )
{
    for ( int i = 0 ;  s [ i ] ;  ++ i )
            estream_putc ( s [ i ] ) ;
    estream_endline ( ) ;
}

int characters ( void )
{
    const char * p [ ] =
    {
        "upper-case: " UPPERS ,
        "lower-case: " LOWERS ,
        "digits: " DIGITS ,
        "punctuation: " PUNCTS ,
        "substitute-character: \t" ,
        "space-at-end-of-line:  " ,
        NULL ,
    } ;
    for ( int i = 0 ;  p [ i ] ;  ++ i )
            put ( p [ i ] ) ;
    return 0 ;
}
