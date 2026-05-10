#include "estream_put_word.h"

#include "estream_put_phrase.h"
#include "estream_put_wsep.h"
#include "hstr_copy.h"
#include "hstr_import.h"
#include "hstr_length.h"
#include "hstr_to_graph.h"

void estream_put_word (
        const char h [ static HSTR_SIZE_MAX ] )
{
    char t [ HSTR_SIZE_MAX ] ;
    hstr_copy ( t , h ) ;
    hstr_to_graph ( t ) ;
    estream_put_wsep ( hstr_length ( t ) ) ;
    estream_put_phrase ( t ) ;
}
