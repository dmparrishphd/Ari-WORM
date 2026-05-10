#include "hstr_clear.h"

#include "mem_clear.h"

void hstr_clear (
        char h [ static HSTR_SIZE_MAX ] )
{
    mem_clear ( h , HSTR_SIZE_MAX ) ;
}
