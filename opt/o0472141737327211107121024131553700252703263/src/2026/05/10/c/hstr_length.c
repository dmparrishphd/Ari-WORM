#include "hstr_length.h"

#include "hstr.h"
#include "hstr_end.h"

int hstr_length (
        const char h [ static HSTR_SIZE_MAX ] )
{
    return hstr_end ( h ) - h ;
}
