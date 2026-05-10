#include "stack.h"

#include "dims.h"
#include "estream.h"
#include "estream_dump_byte.h"
#include "mem_clear.h"
#include "static_assert.h"
#include "whitespace.h"

#include <assert.h>
#include <limits.h>

#include <stdio.h> //-

#define STACK_NMEMB   ( NCORE )

#define N   ( STACK_NMEMB )
STATIC_ASSERT ( ( 2 <= N ) && ( N <= UCHAR_MAX ) ) ;
#define M   ( N - 1 ) // maximum index



enum
{
    none = -1 ,
} ;



struct s_stack
{
    int i ;
    unsigned char a [ NCORE ] ;
} ;
/*  stack members:---
 *
 *      i:  stack pointer: index of next element to be written.
 *      a:  stores elements
 */

typedef
struct s_stack
stack ;






static
stack * const stack_stack (
        const int i )
{
    static stack ss [ NCORE ] ;
    assert ( 0 <= i  &&  i < NCORE ) ;
    return & ss [ i ] ;
}



int stack_reset (
        const int m )
{
    stack * const s = stack_stack ( m ) ;
    assert ( s ) ;
    mem_clear ( s , sizeof ( stack ) ) ;
    s -> i = M ;
    return 0 ;
}



// RETURN NUMBER OF BYTES ON THE STACK. SIMILAR TO
// TING'S { DEPTH }.
static
int length (
        const stack * const s )
{
    assert ( s  &&  s -> i  <=  M ) ;
    const int k = M - s -> i ;
    assert ( 0 <= k  &&  k <= N ) ;
    return k ;
}



int stack_peek (
        const int m )
{
    const stack * const s = stack_stack ( m ) ;
    return length ( s )
            ? s -> a [ s -> i  +  1 ]
            : none ;
}



int stack_pull (
        const int m )
{
    stack * const s = stack_stack ( m ) ;
    return length ( s ) < 1
            ? none
            : s -> a [ ++ s -> i ] ;
}



static
int room (
    const stack * const s )
{
    return N - length ( s ) ;
}



//  RETURN THE NUMBER OF UNUSED BYTES
int stack_room (
        const int m )
{
    return room ( stack_stack ( m ) ) ;
}



int stack_push (
        const int m ,
        const unsigned char u )
{
    stack * const s = stack_stack ( m ) ;
    return ( room ( s ) )
        ? ( s -> a [ s -> i -- ] = u )
        : ( none ) ;
}



int stack_dump (
        const int m )
{
    const stack * s = stack_stack ( m ) ;
    const int w = 3 ; // field width
    int i = s -> i + 1 ;
    while ( i < N  &&  2 * w <= estream_room ( ) )
            estream_dump_byte ( space , s -> a [ i ++ ] ) ;
    return 0 ;
}



int stack_length (
        const int m )
{
    return length ( stack_stack ( m ) ) ;
}



#undef M
#undef N
