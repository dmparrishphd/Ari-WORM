#include "hstr_import.h"

#include "hstr.h"
#include "hstr_clear.h"

#include <string.h>

int hstr_import (
        char h [ static HSTR_SIZE_MAX ] ,
        const char * const s )
{
    hstr_clear ( h ) ;
    if ( ! s ) return 0 ;
    ( void ) strncpy ( h , s , HSTR_LEN_MAX ) ;
    return strcmp ( h , s ) ? -1 : 0 ;
}
