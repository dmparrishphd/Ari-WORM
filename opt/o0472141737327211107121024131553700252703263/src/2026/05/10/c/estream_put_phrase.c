#include "estream_put_phrase.h"

#include "estream.h"
#include "estream_put_hstr.h"
#include "hstr.h"
#include "hstr_length.h"

#include <assert.h>

void estream_put_phrase (
        const char h [ static HSTR_SIZE_MAX ] )
{
    const int n = hstr_length ( h ) ;
    if ( estream_room ( ) < n ) estream_wrap ( ) ;
    assert ( n <= estream_room ( ) ) ;
    estream_put_hstr ( h ) ;
}
