#include "hstr_clean.h"

#include "hstr.h"
#include "mem_clear.h"

#include <string.h>

void hstr_clean (
    char h [ static HSTR_SIZE_MAX ] )
{
    h [ HSTR_INDEX_MAX ] = '\0' ;
    char * const first = strchr ( h , 0 ) ;
    char * const past  = h + HSTR_INDEX_MAX ;
    mem_clear ( first ,  past - first ) ;
}
