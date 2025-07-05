#ifndef H_ESTREAM
#define H_ESTREAM

#include <stddef.h>

#define ESTREAM_WIDTH          ( 80 )
#define ESTREAM_MARGIN_LEFT    (  3 )
#define ESTREAM_MARGIN_RIGHT   (  2 )
#define ESTREAM_TEXT_WIDTH     ( \
    ESTREAM_WIDTH - \
    ESTREAM_MARGIN_LEFT - \
    ESTREAM_MARGIN_RIGHT )

void estream_reset ( void ) ;

void estream_endline ( void ) ;

void estream_flush ( void ) ;

void estream_putc (
    const char ) ;

void estream_put_blank_line ( void ) ;

void estream_wrap ( void ) ;

size_t estream_room ( void ) ;

#endif
