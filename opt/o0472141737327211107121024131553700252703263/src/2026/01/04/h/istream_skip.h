#ifndef H_ISTREAM_SKIP
#define H_ISTREAM_SKIP

#include "hstr.h"
#include "istream.h"

#include <stddef.h>
#include <stdint.h>

#define ISTREAM_SKIP_LIMIT \
        ( ISTREAM_LOGICAL_LINE_LENGTH_MAX )

int istream_skip (
    const size_t ) ;

#endif
