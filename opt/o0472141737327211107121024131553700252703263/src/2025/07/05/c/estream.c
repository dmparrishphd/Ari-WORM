#include "estream.h"

#include "charsetg.h"
#include "charsetp.h"
#include "memclr.h"
#include "whitespace.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#define W   ( ESTREAM_WIDTH )
#define L   ( ESTREAM_MARGIN_LEFT )
#define R   ( ESTREAM_MARGIN_RIGHT )



//SECTION
//Section-name: Constraints
//Section-description:
/*      Establish relationships among:---
 *
 *          -   ESTREAM_WIDTH
 *          -   ESTREAM_MARGIN_LEFT
 *          -   ESTREAM_MARGIN_RIGHT
 *          -   ESTREAM_TEXT_WIDTH
 */

_Static_assert ( 0 < W ,  "" ) ;
_Static_assert ( 0 <= L  &&  L < W  ,   "" ) ;
_Static_assert ( 2 <= L ,   "" ) ;
_Static_assert ( 0 <= R  &&  R < W  ,   "" ) ;
_Static_assert ( 0 <= ( L + R )  &&  ( L + R ) < W  ,   "" ) ;



//SECTION

#define T   ( ESTREAM_TEXT_WIDTH )

#define N   ( L + T )



const char mark_linebreak_hard  = '/'  ;
const char mark_linebreak_soft  = '\\' ;
const char mark_linebreak_reset = '*'  ;



static
struct
{
    //  index of next character to assign:---
    size_t i ;
    //  character data:---
    char a [ N + 1 ] ;
} buffer = { 0 } ;



static int initialized = 0 ;



static
void validate ( void )
{
    size_t i = buffer . i ;
    assert ( L <= i ) ;
    assert ( i <= N ) ;
    assert ( ! buffer . a [ i ] ) ;
}



size_t estream_room ( void )
{
    validate ( ) ;
    return N - buffer . i ;
}



//  Send to standard error the graphic character
//  associated with #0
static
void putg (
        const char c )
{
    unsigned char i = c ;
    char k = charsetg [ i ] ;
    assert ( k == fputc ( k , stderr ) ) ;
}



//  Send to standard error the printing character
//  associated with #0
static
void putp (
        const char c )
{
    unsigned char i = c ;
    char k = charsetp [ i ] ;
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
    memclr ( & buffer , sizeof buffer ) ;
    int i = 0 ;
    if ( i < L - 1 )
            buffer . a [ i ++ ] = c ;
    while ( i < L - 1 )
            buffer . a [ i ++ ] = space ;
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
void export ( void )
{
    validate ( ) ;
    const size_t n = buffer . i ; // number of printing characters
    const size_t f = ! ! n ; // number of final printing characters
    const size_t i = n - f ; // number of initial printing characters
    int j = 0 ;
    for ( ;  j < i ;  ++ j )
            putp ( buffer . a [ j ] ) ;
    if ( f )
            putg ( buffer . a [ j ] ) ;
    putn ( ) ;
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
    unsigned char j = c ;
    buffer . a [ buffer . i ++ ] = charsetp [ j ] ;
    validate ( ) ;
}



#undef L
#undef R
#undef W
