#include "hex.h"

#include "byte.h"
#include "dims.h"



static
int nybl0 (
        const byte b )
{
    return b & 0x0f ;
}

static
int nybl1 (
        const byte b )
{
    return nybl0 ( b >> 4u ) ;
}



const char * const hex = "0123456789ABCDEF" ;

const char hex_hi (
        const byte b )
{
    return hex [ nybl1 ( b ) ] ;
}

const char hex_lo (
        const byte b )
{
    return hex [ nybl0 ( b ) ] ;
}
