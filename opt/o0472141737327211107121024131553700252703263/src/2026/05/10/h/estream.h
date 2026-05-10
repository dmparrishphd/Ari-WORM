#ifndef H_ESTREAM
#define H_ESTREAM

#define ESTREAM_HEIGHT         ( 24 )

#define ESTREAM_WIDTH          ( 80 )
#define ESTREAM_MARGIN_LEFT    (  3 )
#define ESTREAM_MARGIN_RIGHT   (  2 )
#define ESTREAM_TEXT_WIDTH     ( \
    ESTREAM_WIDTH - \
    ESTREAM_MARGIN_LEFT - \
    ESTREAM_MARGIN_RIGHT )

//TODO: Constrain ESTREAM_HEIGHT

#define ESTREAM_KW_ERROR     "ERROR"
#define ESTREAM_KW_WARNING   "WARNING"
#define ESTREAM_KW_NOTE      "NOTE"

void estream_reset ( void ) ;

void estream_flush ( void ) ;

void estream_endline ( void ) ;

void estream_putc (
    const char ) ;

void estream_putx ( void ) ;

void estream_put_blank_line ( void ) ;

void estream_put_gap ( void ) ;

void estream_trunc ( void ) ;

void estream_wrap ( void ) ;

int estream_room ( void ) ;

#endif
