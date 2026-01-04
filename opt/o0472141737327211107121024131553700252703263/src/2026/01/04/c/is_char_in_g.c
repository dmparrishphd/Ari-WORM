#include "is_char_in_g.h"

#include "charsets.h"

int is_char_in_g (
        const char c )
{
    unsigned char u = c ;
    unsigned char k = chrg ( u ) ;
    return ! ! ( k == u ) ;
}
