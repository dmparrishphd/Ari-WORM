#include "hstr_cat.h"

#include "hstr.h"
#include "hstr_clean.h"
#include "hstr_import.h"
#include "hstr_length.h"
#include "hstr_room.h"

#include <string.h>



int hstr_cat (
        char h [ static HSTR_SIZE_MAX ] ,
        const char * const s )
{
    hstr_clean ( h ) ;
    const int n = hstr_room ( h ) ;
    ////////
    char g [ HSTR_SIZE_MAX ] ;
    const int v =
            hstr_import ( g , s ) ||
            n < hstr_length ( g ) ;
    ////////
    ( void ) strncat ( h , s , n ) ;
    return v ? -1 : 0 ;
}
