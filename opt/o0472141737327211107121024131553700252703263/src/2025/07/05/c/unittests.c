#include "unittests.h"

#include "charset.h"
#include "estream.h"
#include "estream_put_error.h"
#include "estream_put_msg.h"
#include "estream_put_note.h"
#include "estream_put_warning.h"
#include "memclr.h"
#include "trace.h"
#include "whitespace.h"

#include <assert.h>
#include <string.h>



static
void test_memclr ( void )
{
    char a [ ] = "This is a test." ;
    memclr ( a , sizeof a ) ;
    for ( int i = 0 ;  i < sizeof a ;  ++ i )
            assert ( ! a [ i ] ) ;
}



#define LIST \
    " estream_put_note," \
    " estream_put_warning and" \
    " estream_put_error"
void test__note_warning_error ( void )
{
    estream_put_note ( TRACE ,
            "Testing" LIST ":---" ) ;
    const char * const msg =
            "Cancel---this is only a test." ;
    estream_put_warning ( TRACE , msg ) ;
    estream_put_error ( TRACE , msg ) ;
    estream_put_note ( TRACE ,
            "Done testing" LIST "." ) ;
}
#undef LIST



static
void test_estream ( void )
{
    estream_put_note ( TRACE ,
            "Testing estream:---" ) ;
    ////////
    estream_put_note ( TRACE ,
            "The next line should be blank." ) ;
    estream_put_blank_line ( ) ;
    estream_put_note ( TRACE ,
            "The previous line should be blank." ) ;
    estream_endline ( ) ;
    ////////
    estream_put_note ( TRACE , "Trailing spaces"
            " are printed using"
            " a substitute graphic character." ) ;
    estream_put_note ( TRACE , "The next line"
            " should have a space and"
            " a trailing space:---" ) ;
    estream_putc ( space ) ;
    estream_putc ( space ) ;
    estream_endline ( ) ;
    estream_put_note ( TRACE , "The previous line"
            " should have a space and a trailing space." ) ;
    ////////
    estream_put_note ( TRACE ,
            "The estream character set:---" ) ;
    for ( int c = CHAR_MIN ;  c <= CHAR_MAX ;  ++ c )
            estream_putc ( c ) ;
    estream_endline ( ) ;
    ////////
    estream_put_note ( TRACE ,
            "Done testing estream." ) ;
}



int unittests ( void )
{
    test_memclr ( ) ;
    test__note_warning_error ( ) ;
    test_estream ( ) ;
    return 0 ;
}
