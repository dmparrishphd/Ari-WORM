#ifndef H_ISTREAM
#define H_ISTREAM

#include "estream.h"
#include "hstr.h"

#define ISTREAM_HEIGHT \
        ( ESTREAM_HEIGHT )

#define ISTREAM_TEXT_WIDTH \
        ( ESTREAM_TEXT_WIDTH )

#define ISTREAM_LOGICAL_LINE_LENGTH_MAX \
        ( 2 * ISTREAM_TEXT_WIDTH )

int istream_error ( void ) ;

int istream_eof ( void ) ;

#endif
