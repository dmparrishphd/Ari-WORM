#include "hstr.h"

#include "hstr_length.h"
#include "mem_rev.h"

void hstr_rev (
        char h [ static HSTR_SIZE_MAX ] )
{
    mem_rev ( h , hstr_length ( h ) ) ;
}
