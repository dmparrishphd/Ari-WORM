#include "is_char_in_p.h"

#include "charsets.h"

int is_char_in_p (
        const char c )
{
    return ! ! ( c == chr_print ( c ) ) ;
}
