#include "unittests.h"

#include "args.h"
#include "args_dump.h"
#include "charsets.h"
#include "do.h"
#include "estream.h"
#include "estream_display_hstr.h"
#include "estream_put_text.h"
#include "estream_pose.h"
#include "estream_put_bullet.h"
#include "estream_put_charset_p.h"
#include "estream_put_error.h"
#include "estream_put_note.h"
#include "estream_put_phrase.h"
#include "estream_dump_byte.h"
#include "estream_puts.h"
#include "estream_put_warning.h"
#include "estream_put_word.h"
#include "go.h"
#include "hstr.h"
#include "hstr_clean.h"
#include "hstr_clear.h"
#include "hstr_import.h"
#include "hstr_length.h"
#include "hstr_rev.h"
#include "is_char_in_g.h"
#include "is_char_in_p.h"
#include "is_hstr.h"
#include "is_hstr_blank.h"
#include "istream.h"
#include "istream_readline.h"
#include "mem_clear.h"
#include "mem_swap.h"
#include "mem_rev.h"
#include "stack.h"
#include "tracer.h"
#include "whitespace.h"

#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



static
void test__mem_clear ( void )
{
    char a [ ] = "This is a test." ;
    const size_t n = sizeof a ;
    mem_clear ( a , n ) ;
    for ( int i = 0 ;  i < n ;  ++ i )
            assert ( ! a [ i ] ) ;
}



static
void test__mem_swap ( void )
{
    unsigned char a = 0 ;
    unsigned char b = 1 ;
    mem_swap ( & a ,  & b ) ;
    assert ( a == 1 ) ;
    assert ( b == 0 ) ;
}



#define N   ( HSTR_SIZE_MAX )
static
void test__hstr_clear ( void )
{
    char a [ N ] ;
    ( void ) memset ( a , N , 'A' ) ;
    hstr_clear ( a ) ;
    for ( int i = 0 ;  i < N ;  ++ i )
            assert ( ! a [ i ] ) ;
}
#undef N



static
void test__hstr_import ( void )
{
    char h [ HSTR_SIZE_MAX ] = { 0 } ;
    assert ( ! hstr_import ( h , "" ) ) ;
    assert ( ! h [ 0 ] ) ;
    const char * const phrase = "A phrase!" ;
    assert ( ! hstr_import ( h , phrase ) ) ;
    {
        assert ( ! strcmp ( h , phrase ) ) ;
        const char * const longphrase =
                "the quick brown fox jumped over the lazy dog."
                "the quick brown fox jumped over the lazy dog."
                "the quick brown fox jumped over the lazy dog." ;
        assert ( HSTR_LEN_MAX < strlen ( longphrase ) ) ;
        assert ( hstr_import ( h , longphrase ) < 0 ) ;
    }
}



static
void test__is_hstr ( void )
{
    char a [ 2 * HSTR_SIZE_MAX ] = { 0 } ;
    assert ( ! hstr_import ( a , "" ) ) ;
    assert ( is_hstr ( a ) ) ;
    mem_clear ( a , 2 * HSTR_SIZE_MAX ) ;
    memset ( a , 'A' , HSTR_SIZE_MAX ) ;
    assert ( HSTR_LEN_MAX < strlen ( a ) ) ;
    assert ( ! is_hstr ( a ) ) ;
}



static
void test__charmaps ( void )
{
    assert ( isgraph ( chr_graph ( space ) ) ) ;
    assert ( isgraph ( chr_graph ( newline ) ) ) ;
    for ( int i = 0 ;  i <= UCHAR_MAX ;  ++ i )
    {
        assert ( isgraph ( chr_graph ( i ) ) ) ;
        assert ( isprint ( chr_print ( i ) ) ) ;
        if ( chr_print ( i ) != space )
                assert ( chr_print ( i ) == chr_graph ( i ) ) ;
    }
}



static
void test__is_char_in_p ( void )
{
    for ( int i = CHAR_MIN ;  i <= CHAR_MAX ;  ++ i )
    {
        int in = is_char_in_p ( i ) ;
        assert ( 0 <= in  &&  in <= 1 ) ;
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
void test__enquote ( void )
{
    TRACER_DECLARE ;
    estream_put_note ( TRACER , "__LINE__ == " ENQUOTE ( __LINE__ ) ) ;
    estream_put_note ( TRACER , "INT_MAX == " ENQUOTE ( INT_MAX ) ) ;
}



static
void test__estream ( void )
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
                    k = 0 ,  estream_endline ( ) ;
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



void test__estream_pose ( void )
{
    TRACER_DECLARE ;
    estream_put_note ( TRACER ,
            "Testing estream_pose:---" ) ;
    estream_endline ( ) ;
    assert ( ! estream_pose ( ) ) ;
    estream_put_note ( TRACER ,
            "Done testing test__estream_pose" ) ;
}



void test__estream_put_text ( void )
{
    TRACER_DECLARE ;
    estream_put_note ( TRACER ,
            "Testing estream_put_text:---" ) ;
    estream_put_text ( NULL ) ;
    estream_put_text ( "" ) ;
    estream_put_text (
            "This song is just six words long." ) ;
    estream_put_text ( 
            "short-word"
            " "
            "(really-long-word):"
            "abcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstuvwxyz"
            "abcdefghijklmnopqrstuvwxyz" ) ;
    estream_put_text ( "This sentence is short." ) ;
    const char * const song =
            "Let's repeat this song, then:"
            " Let's repeat this song, then:" ;
    estream_put_text ( song ) ;
    estream_put_text ( song ) ;
    estream_put_note ( TRACER ,
            "Done testing test__estream_put_text" ) ;
}



static
void test__is_hstr_blank ( void )
{
    char h [ HSTR_SIZE_MAX ] = { 0 } ;
    assert ( is_hstr_blank ( h ) ) ;
    memset ( h , space , HSTR_LEN_MAX ) ;
    h [ HSTR_INDEX_MAX ] = '\0' ;
    assert ( is_hstr_blank ( h ) ) ;
}




static
void test__estream_dump_byte ( void )
{
    TRACER_DECLARE ;
    estream_put_note ( TRACER ,
            "Testing estream_dump_byte:---" ) ;
    {
        for ( int i = 0 ;  i <= UCHAR_MAX ;  ++ i )
                estream_dump_byte ( 0 , i ) ;
        estream_endline ( ) ;
    }
    {
        for ( int i = 0 ;  i <= UCHAR_MAX ;  ++ i )
                estream_dump_byte ( space , i ) ;
        estream_endline ( ) ;
    }
    {
        for ( int i = 0 ;  i <= UCHAR_MAX ;  ++ i )
                estream_dump_byte ( chr_noprint , i ) ;
        estream_endline ( ) ;
    }
    estream_put_note ( TRACER ,
            "Done testing estream_dump_byte." ) ;
}



static
void test__istream_readline ( int flag )
{
    if ( ! flag ) return ;
    char h [ HSTR_SIZE_MAX ] ;
    istream_readline ( h ) ;
    estream_display_hstr ( h ) ;
}



void test__estream_put_phrase ( void )
{
    TRACER_DECLARE ;
    estream_put_note ( TRACER ,
            "Testing estream_put_phrase:---" ) ;
    args a = { 0 } ;
    assert ( ! args_dump ( & a ) ) ;
    estream_put_note ( TRACER ,
            "Done testing estream_put_phrase." ) ;
}



void test__estream_put_word ( void )
{
    TRACER_DECLARE ;
    estream_put_note ( TRACER ,
            "Testing estream_put_word:---" ) ;
    char h [ HSTR_SIZE_MAX ] ;
    hstr_import ( h , "As you wish!" ) ;
    estream_put_word ( h ) ;
    hstr_import ( h , "And another thing!" ) ;
    estream_put_word ( h ) ;
    hstr_import ( h , "And another!" ) ;
    estream_put_word ( h ) ;
    estream_put_word ( h ) ;
    estream_put_word ( h ) ;
    estream_put_word ( h ) ;
    estream_put_word ( h ) ;
    estream_put_word ( h ) ;
    estream_endline ( ) ;
    {
        char h [ HSTR_SIZE_MAX ] = { 0 } ;
        memset ( h , 'G' , HSTR_LEN_MAX ) ;
        assert ( HSTR_LEN_MAX == hstr_length ( h ) ) ;
        char * g = "FULL-LENGTH--SHORT-STRING" ;
        memcpy ( h , g , strlen ( g ) < HSTR_LEN_MAX ? strlen ( g ) : HSTR_LEN_MAX ) ;
        estream_put_word ( h ) ;
    }
    estream_put_note ( TRACER ,
            "Done testing test__estream_put_word" ) ;
}



static
void test__args ( void )
{
    TRACER_DECLARE ;
    estream_put_note ( TRACER ,
            "Testing args:---" ) ;
    char g [ HSTR_SIZE_MAX ] = { 0 } ;
    char h [ HSTR_SIZE_MAX ] = { 0 } ;
    args a = { 0 } ;
    {
        estream_put_note ( TRACER , "" ) ;
        assert ( ! hstr_import ( h , "" ) )  ;
        args_import ( & a , h ) ;
        assert ( ! args_nmemb ( & a ) ) ;
    }
    {
        #define A   "A"
        #define X   " "
        #define N   ( 4 )
        const char * const aa [ N ] =
        {
            A ,
            A X ,
            X A ,
            X A X ,
        } ;
        for ( int i = 0 ;  i < N ;  ++ i )
        {
            estream_put_note ( TRACER , "" ) ;
            assert ( ! hstr_import ( h , aa [ i ] ) )  ;
            args_import ( & a , h ) ;
            assert ( 1 == args_nmemb ( & a ) ) ;
            args_fetch ( g , & a , 0 ) ;
            assert ( ! strcmp ( A , g ) ) ;
        }
        #undef A
        #undef X
        #undef N
    }
    {
        estream_put_note ( TRACER , "" ) ;
        hstr_clear ( h ) ;
        for ( int i = 0 ; ; )
        {
            static int j = 0 ;
            h [ i ] = ( j ++ ) % 26 + 'A' ;
            if ( ++ i == HSTR_INDEX_MAX ) break ;
            h [ i ] = space ;
            if ( ++ i == HSTR_INDEX_MAX ) break ;
        }
        args_import ( & a , h ) ;
        int n = args_nmemb ( & a ) ;
        assert ( n == HSTR_SIZE_MAX / 2 ) ;
        estream_endline ( ) ;
        for ( int i = 0 ;  i < n ;  ++ i )
        {
            char g [ HSTR_SIZE_MAX ] ;
            args_fetch ( g ,  & a ,  i ) ;
            estream_put_word ( g ) ;
        }
        estream_endline ( ) ;
    }
    {
        estream_put_note ( TRACER , "" ) ;
        char hh [ 2 * HSTR_SIZE_MAX ] = { 0 } ;
        memset ( hh , 'X' , 2 * HSTR_SIZE_MAX - 1 ) ;
        args_import ( & a ,  hh ) ;
    }
    estream_put_note ( TRACER ,
            "Done testing args" ) ;
}



static
void test__args_dump ( void )
{
    TRACER_DECLARE ;
    estream_put_note ( TRACER ,
            "Testing args_dump:---" ) ;
    args a = { 0 } ;
    assert ( ! args_dump ( & a ) ) ;
    char h [ HSTR_SIZE_MAX ] ;
    {
        assert ( ! hstr_import ( h ,  "This is a test" ) ) ;
        assert ( ! args_import ( & a ,  h ) ) ;
        assert ( ! args_dump ( & a ) ) ;
    }
    {
        assert ( ! hstr_import ( h ,
                "When parsing,  KIS.   \a\b\f\n\r\t\v" ) ) ;
        assert ( ! args_import ( & a ,  h ) ) ;
        assert ( ! args_dump ( & a ) ) ;
    }
    {
        hstr_clear ( h ) ;
        h [ 0 ] = chr_noprint ;
        assert ( ! args_import ( & a ,  h ) ) ;
        assert ( ! args_dump ( & a ) ) ;
    }
    {
        memset ( h , chr_noprint , HSTR_SIZE_MAX ) ;
        hstr_clean ( h ) ;
        assert ( ! args_import ( & a ,  h ) ) ;
        assert ( ! args_dump ( & a ) ) ;
    }
    estream_put_note ( TRACER ,
            "Done testing args_dump" ) ;
}



static
void test__ari_query ( void )
{
    TRACER_DECLARE ;
    estream_put_note ( TRACER ,
            "Testing ari_query:---" ) ;

    estream_put_note ( TRACER ,
            "Done testing args_dump" ) ;
}



static
void test__ari_stack ( void )
{
    TRACER_DECLARE ;
    estream_put_note ( TRACER ,
            "Testing ari_stack:---" ) ;
    const int n = 42 ;
    const int ns = 0 ;
    {
        // peeking an empty stack
        estream_put_note ( TRACER , "" ) ;
        stack_reset ( ns ) ;
        assert ( stack_peek ( ns ) < 0 ) ;
    }
    {
        // pulling from an empty stack
        estream_put_note ( TRACER , "" ) ;
        stack_reset ( ns ) ;
        assert ( ! stack_length ( ns ) ) ;
        assert ( stack_pull ( ns ) < 0 ) ;
    }
    {
        // pushing an empty stack
        // peeking a non-empty stack
        estream_put_note ( TRACER , "" ) ;
        stack_reset ( ns ) ;
        assert ( n == stack_push ( ns , n ) ) ;
        assert ( n == stack_peek ( ns ) ) ;
    }
    {
        // pushing to an empty stack, then pulling
        estream_put_note ( TRACER , "" ) ;
        stack_reset ( ns ) ;
        assert ( ! stack_length ( ns ) ) ;
        assert ( n == stack_push ( ns , n ) ) ;
        assert ( n == stack_peek ( ns ) ) ;
        assert ( n == stack_pull ( ns ) ) ;
        // stack should be empty, now
        assert ( stack_pull ( ns ) < 0 ) ;
        assert ( ! stack_length ( ns ) ) ;
    }
    {
        // pushing to a full stack
        estream_put_note ( TRACER , "" ) ;
        // fill the stack
        stack_reset ( ns ) ;
        while ( stack_room ( ns ) )
                assert ( n == stack_push ( ns , n ) ) ;
        assert ( n != stack_push ( ns , n ) ) ;
        // empty the stack
        while ( stack_length ( ns ) )
                assert ( n == stack_peek ( ns ) ) ,
                assert ( n == stack_pull ( ns ) ) ;
        assert ( stack_pull ( ns ) < 0 ) ;
    }
    ////////
    estream_put_note ( TRACER ,
            "Done testing args_stack" ) ;
}



int unittests ( void )
{
    test__mem_swap ( ) ;
    test__mem_clear ( ) ;
    test__hstr_clear ( ) ;
    test__hstr_import ( ) ;
    test__is_hstr ( ) ;
    test__charmaps ( ) ;
    test__is_char_in_p ( ) ;
    test__is_char_in_g ( ) ;
    test__note_warning_error ( ) ;
    test__enquote ( ) ;
    test__estream ( ) ;
    test__estream_dump_byte ( ) ;
    test__is_hstr_blank ( ) ;
    test__istream_readline ( 0 ) ;
    test__estream_put_phrase ( ) ;
    test__estream_put_word ( ) ;
    test__estream_pose ( ) ;
    test__estream_put_text ( ) ;
    //TODO: make separate tests that read stdin:---
    test__args ( ) ;
    test__args_dump ( ) ;
    test__ari_query ( ) ;
    test__ari_stack ( ) ;
    return 0 ;
}
