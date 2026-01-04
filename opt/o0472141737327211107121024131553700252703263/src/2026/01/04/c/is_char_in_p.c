#include "is_char_in_p.h"

#include "charsets.h"

int is_char_in_p (
        const char c )
{
    unsigned char u = c ;
    unsigned char k = chrp ( u ) ;
    return ! ! ( k == u ) ;
}
