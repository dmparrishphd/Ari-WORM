#include "hstr_room.h"

#include "hstr_length.h"

int hstr_room (
        const char h [ static HSTR_SIZE_MAX ] )
{
    return HSTR_LEN_MAX - hstr_length ( h ) ;
}
