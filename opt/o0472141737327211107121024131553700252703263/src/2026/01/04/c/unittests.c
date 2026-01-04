#include "unittests.h"

#include "charsets.h"
#include "do.h"
#include "estream.h"
#include "estream_put_bullet.h"
#include "estream_put_charset_p.h"
#include "estream_put_error.h"
#include "estream_put_note.h"
#include "estream_puts.h"
#include "estream_put_warning.h"
#include "go.h"
#include "hstr.h"
#include "hstr_clear.h"
#include "is_char_in_g.h"
#include "is_char_in_p.h"
#include "is_hstr_blank.h"
#include "istream.h"
#include "memclr.h"
#include "tracer.h"
#include "whitespace.h"

#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



static
void test_memclr ( void )
{
    char a [ ] = "This is a test." ;
    const size_t n = sizeof a ;
    memclr ( a , n ) ;
    for ( int i = 0 ;  i < n ;  ++ i )
            assert ( ! a [ i ] ) ;
}



#define N   ( HSTR_SIZE_MAX )
static
void test_hstr_clear ( void )
{
    char a [ N ] ;
    ( void ) memset ( a , N , 'A' ) ;
    hstr_clear ( a ) ;
    for ( int i = 0 ;  i < N ;  ++ i )
            assert ( ! a [ i ] ) ;
}
#undef N



static
void test_charmaps ( void )
{
    assert ( isgraph ( chrg ( space ) ) ) ;
    assert ( isgraph ( chrg ( newline ) ) ) ;
    for ( int i = 0 ;  i <= UCHAR_MAX ;  ++ i )
    {
        assert ( isgraph ( chrg ( i ) ) ) ;
        assert ( isprint ( chrp ( i ) ) ) ;
        if ( chrp ( i ) != space )
                assert ( chrp ( i ) == chrg ( i ) ) ;
    }
}



static
void test__is_char_in_p ( void )
{
    for ( int i = CHAR_MIN ;  i <= CHAR_MAX ;  ++ i )
    {
        int tf = is_char_in_p ( i ) ;
        assert ( 0 <= tf  &&  tf <= 1 ) ;
    }
}



static
void test__is_char_in_g ( void )
{
    for ( int i = CHAR_MIN ;  i <= CHAR_MAX ;  ++ i )
    {
        int in = is_char_in_g ( i ) ;
        assert ( 0 <= in  &&  in <= 1 ) ;
        if ( in ) assert ( is_char_in_p ( i ) ) ;
    }
}



#define CANCEL    "CANCEL "
#define ONLY_A_TEST   "---this is only a test."
static
void test__note_warning_error ( void )
{
    TRACER_DECLARE ;
    estream_put_note (
        TRACER , CANCEL ESTREAM_KW_NOTE    ONLY_A_TEST ) ;
    estream_put_warning (
        TRACER , CANCEL ESTREAM_KW_WARNING ONLY_A_TEST ) ;
    estream_put_error (
        TRACER , CANCEL ESTREAM_KW_ERROR   ONLY_A_TEST ) ;
}
#undef CANCEL
#undef ONLY_A_TEST



static
void test_enquote ( void )
{
    TRACER_DECLARE ;
    estream_put_note ( TRACER , "__LINE__ == " ENQUOTE ( __LINE__ ) ) ;
    estream_put_note ( TRACER , "INT_MAX == " ENQUOTE ( INT_MAX ) ) ;
}



static
void test_estream ( void )
{
    TRACER_DECLARE ;
    estream_put_note ( TRACER ,
            "Testing estream:---" ) ;
    ////////
    estream_put_note ( TRACER ,
            "The next line should be blank." ) ;
    estream_put_blank_line ( ) ;
    estream_put_note ( TRACER ,
            "The previous line should be blank." ) ;
    ////////
    estream_put_note ( TRACER ,
            "Character set P includes only"
            " the space character and"
            " the characters:---" ) ;
    estream_put_charset_p ( ) ;
    ////////
    estream_put_note ( TRACER ,
            "The substitute graphic character is:---" ) ;
    estream_putc ( '\t' ) ;
    estream_endline ( ) ;
    ////////
    estream_put_note ( TRACER ,
            "Characters that are not part of character set P"
            " are printed using"
            " a substitute graphic character."
            " The substitute graphic character"
            " for nonprinting characters is:---" ) ;
    estream_putc ( '\t' ) ;
    estream_endline ( ) ;
    ////////
    estream_put_note ( TRACER ,
            "Trailing spaces"
            " are printed using"
            " a substitute graphic character."
            " The substitute graphic character"
            " for trailing spaces is:---" ) ;
    estream_putx ( ) ;
    estream_endline ( ) ;
    ////////
    #define W   ( ESTREAM_TEXT_WIDTH )
    estream_put_note ( TRACER ,
            "Writing all the characters to the standard error stream:---" ) ;
    {
        int k = 0 ; // characters written on the current line
        for ( int c = CHAR_MIN ;  c <= CHAR_MAX ;  ++ c , ++ k )
        {
            if ( estream_room ( ) < 2  ||  32 <= k )
                    k = 0 ,  estream_wrap ( ) ;
            if ( k ) estream_putx ( ) ;
            else    assert ( W == estream_room ( ) ) ;
            estream_putc ( c ) ;
        }
    }
    estream_endline ( ) ;
    #undef W
    ////////
    estream_put_note ( TRACER , "CHAR_MIN == " ENQUOTE ( CHAR_MIN ) ) ;
    estream_put_note ( TRACER , "CHAR_MAX == " ENQUOTE ( CHAR_MAX ) ) ;
    ////////
    estream_put_note ( TRACER ,
            "Done testing estream." ) ;
}



static
void test_is_hstr_blank ( void )
{
    char h [ HSTR_SIZE_MAX ] = { 0 } ;
    assert ( is_hstr_blank ( h ) ) ;
    memset ( h , space , HSTR_LEN_MAX ) ;
    h [ HSTR_INDEX_MAX ] = '\0' ;
    assert ( is_hstr_blank ( h ) ) ;
}



int unittests ( void )
{
    test_memclr ( ) ;
    test_hstr_clear ( ) ;
    test_charmaps ( ) ;
    test__is_char_in_p ( ) ;
    test__is_char_in_g ( ) ;
    test__note_warning_error ( ) ;
    test_enquote ( ) ;
    test_estream ( ) ;
    test_is_hstr_blank ( ) ;
    return 0 ;
}
