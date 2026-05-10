#include "is_hstr_blank.h"

#include "hstr.h"
#include "whitespace.h"

int is_hstr_blank (
        const char h [ static HSTR_SIZE_MAX ] )
{
    for ( int i = 0 ;  h [ i ]  &&  i < HSTR_INDEX_MAX ;  ++ i )
            if ( space != h [ i ] ) return 0 ;
    return 1 ;
}
