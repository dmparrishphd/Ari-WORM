#include "estream.h"

#include "byte.h"
#include "charsets.h"
#include "is_char_in_g.h"
#include "is_char_in_p.h"
#include "mem_clear.h"
#include "static_assert.h"
#include "whitespace.h"

#include <assert.h>
#include <limits.h>
#include <stdio.h>

#define W   ( ESTREAM_WIDTH )
#define L   ( ESTREAM_MARGIN_LEFT )
#define R   ( ESTREAM_MARGIN_RIGHT )



STATIC_ASSERT ( 0 <  W  &&  W <= UCHAR_MAX ) ;
STATIC_ASSERT ( 2 <= L  &&  L <  W         ) ;
STATIC_ASSERT ( 2 <= R  &&  R <  W         ) ;
STATIC_ASSERT ( L + R  <  W ) ;



#define N   ( L + ESTREAM_TEXT_WIDTH )



const char mark_linebreak_hard  = '~'  ;
const char mark_linebreak_soft  = '\\' ;
const char mark_linebreak_reset = '*'  ;
const char mark_linebreak_trunc = '|'  ;



static
struct
{
    //  last character written:---
    int z ;
    //  index of next character to assign:---
    int i ;
    //  character data:---
    char a [ N + 1 ] ;
} buffer = { 0 } ;



static int initialized = 0 ;



static
void validate ( void )
{
    int i = buffer . i ;
    assert ( L <= i ) ;
    assert ( i <= N ) ;
    assert ( ! buffer . a [ i ] ) ;
}



int estream_room ( void )
{
    validate ( ) ;
    return N  -  buffer . i ;
}



//  Send to standard error the graphic character
//  associated with #0
static
void putg (
        const char c )
{
    byte i = c ;
    char k = chr_graph ( i ) ;
    assert ( k == fputc ( k , stderr ) ) ;
}



//  Send to standard error the printing character
//  associated with #0
static
void putp (
        const char c )
{
    byte i = c ;
    char k = chr_print ( i ) ;
    assert ( k == fputc ( k , stderr ) ) ;
}



static
void putn ( void )
{
    assert ( newline == fputc ( newline , stderr ) ) ;
}



static
void linebreak_inner (
        const char c )
{
    mem_clear ( & buffer ,  sizeof buffer ) ;
    int i = 0 ;
    if    ( i < L - 1 )
            buffer . a [ i ++ ] = c ;
    while ( i < L - 1 )
            buffer . a [ i ++ ] = space ;
    //THEN
            buffer . a [ i ++ ] = space ;
            buffer . i = i ;
}



static
void linebreak (
        const char c )
{
    validate ( ) ;
    linebreak_inner ( c ) ;
    validate ( ) ;
}



void estream_reset ( void )
{
    if ( initialized ) return ;
    linebreak_inner ( mark_linebreak_reset ) ;
    validate ( ) ;
    initialized = 1 ;
}



static
void reset_trunc ( void )
{
    validate ( ) ;
    linebreak ( mark_linebreak_trunc ) ;
    assert ( estream_room ( ) ) ;
    validate ( ) ;
}



static
void reset_wrap ( void )
{
    validate ( ) ;
    linebreak ( mark_linebreak_soft ) ;
    assert ( estream_room ( ) ) ;
    validate ( ) ;
}



static
void reset_newline ( void )
{
    validate ( ) ;
    linebreak ( mark_linebreak_hard ) ;
    validate ( ) ;
}



static
void export_line (
        const int i ,
        const int f )
{
    int j = 0 ;
    for ( ;  j < i ;  ++ j ) putp ( buffer . a [ j ] ) ;
    if  (        f         ) putg ( buffer . a [ j ] ) ;
}



static
void export_left_margin ( void )
{
    // first character must be a graphic characer:---
    assert ( is_char_in_g ( buffer . a [ 0 ] ) ) ;
    // find index of last graphic character:---
    int j = L - 1 ;
    for ( ;  j ;  -- j )
    {
        const char c = buffer . a [ j ] ;
        assert ( is_char_in_p ( c ) ) ;
        if ( is_char_in_g ( c ) ) break ;
    }
    for ( int k = 0 ;  k <= j ;  ++ k )
            putp ( buffer . a [ k ] ) ;
}



static
void export ( void )
{
    validate ( ) ;
    const int n = buffer . i ; // number of         printing characters
    const int f = ! ! n ;      // number of   final printing characters
    const int i = n - f ;      // number of initial printing characters
    /**/ if ( L < n ) // There are characters beyond the left margin.
            export_line ( i , f ) ;
    else if ( L ) // There is a left margin.
            export_left_margin ( ) ;
    else ;
    putn ( ) ;
}



void estream_trunc ( void )
{
    validate ( ) ;
    export ( ) ;
    reset_trunc ( ) ;
    validate ( ) ;
}



void estream_wrap ( void )
{
    validate ( ) ;
    export ( ) ;
    reset_wrap ( ) ;
    validate ( ) ;
}



void estream_endline ( void )
{
    validate ( ) ;
    if ( buffer . i == L )
    {
        // already at the end of the line
        buffer . a [ 0 ] = mark_linebreak_hard ;
    }
    else
    {
        export ( ) ;
        reset_newline ( ) ;
    }
    validate ( ) ;
}



void estream_put_blank_line ( void )
{
    validate ( ) ;
    estream_endline ( ) ;
    reset_newline ( ) ;
    export ( ) ;
    validate ( ) ;
}



void estream_put_gap ( void )
{
    validate ( ) ;
    putn ( ) ;
    validate ( ) ;
}



void estream_flush ( void )
{
    validate ( ) ;
    estream_wrap ( ) ;
    validate ( ) ;
}



void estream_putc (
        const char c )
{
    validate ( ) ;
    if ( ! estream_room ( ) ) estream_wrap ( ) ;
    byte j = c ;
    buffer . a [ buffer . i ++ ] = chr_print ( j ) ;
    validate ( ) ;
}



void estream_putx ( void )
{
    estream_putc ( space ) ;
}



#undef L
#undef N
#undef R
#undef W
