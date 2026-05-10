#include "hstr_end.h"

#include "hstr.h"

#include <assert.h>
#include <string.h>

const char * const hstr_end (
        const char h [ static HSTR_SIZE_MAX ] )
{
    assert ( h ) ;
    const char * const p = memchr ( h , 0 , HSTR_SIZE_MAX ) ;
    return p ? p : h + HSTR_INDEX_MAX ;
}
