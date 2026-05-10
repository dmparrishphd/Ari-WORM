#include "is_char_in_g.h"

#include "charsets.h"

int is_char_in_g (
        const char c )
{
    return ! ! ( c == chr_graph ( c ) ) ;
}
