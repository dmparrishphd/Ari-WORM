#include "is_hstr.h"

#include "hstr.h"
#include "hstr_end.h"

#include <assert.h>

int is_hstr (
        const char h [ static HSTR_SIZE_MAX ] )
{
    if ( ! h ) return 0 ;
    const char * const p = hstr_end ( h ) ;
    assert ( p ) ;
    return * p ? 0 : 1 ;
}
