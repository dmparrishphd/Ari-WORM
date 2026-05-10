#include "is_hstr_of_p.h"

#include "hstr.h"
#include "is_char_in_p.h"

int is_hstr_of_p (
        const char h [ static HSTR_SIZE_MAX ] )
{
    for ( int i = 0 ;  h [ i ]  &&  i < HSTR_INDEX_MAX ;  ++ i )
            if ( ! is_char_in_p ( h [ i ] ) ) return 0 ;
    return 1 ;
}
