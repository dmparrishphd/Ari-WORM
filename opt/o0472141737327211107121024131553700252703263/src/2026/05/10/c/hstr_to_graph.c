#include "hstr_to_graph.h"

#include "hstr.h"
#include "hstr_clean.h"
#include "is_hstr_of_g.h"
#include "charsets.h"

int hstr_to_graph (
        char h [ static HSTR_SIZE_MAX ] )
{
    hstr_clean ( h ) ;
    if ( is_hstr_of_g ( h ) )
        return 0 ;
    for ( int i = 0 ;  h [ i ] ;  ++ i )
            h [ i ] = chr_graph ( h [ i ] ) ;
    return -1 ;
}
#undef N
