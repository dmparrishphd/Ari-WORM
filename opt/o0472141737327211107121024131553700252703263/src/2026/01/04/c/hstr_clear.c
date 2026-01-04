#include "hstr_clear.h"

#include "memclr.h"

void hstr_clear (
        char h [ static HSTR_SIZE_MAX ] )
{
    memclr ( h , HSTR_SIZE_MAX ) ;
}
