#include "ari.h"

#include "args.h"
#include "dims.h"
#include "byte.h"
#include "do.h"
#include "estream.h"
#include "estream_alert.h"
#include "estream_display_hstr.h"
#include "estream_dump_byte.h"
#include "estream_display_hstr.h"
#include "estream_put_warning.h"
#include "estream_put_error.h"
#include "estream_put_guide.h"
#include "estream_put_hstr.h"
#include "estream_put_note.h"
#include "estream_put_phrase.h"
#include "estream_put_word.h"
#include "estream_puts.h"
#include "hex.h"
#include "hstr.h"
#include "hstr_cat.h"
#include "hstr_clear.h"
#include "hstr_import.h"
#include "hstr_length.h"
#include "hstr_rev.h"
#include "is_hstr_blank.h"
#include "isa.h"
#include "mem_clear.h"
#include "operation.h"
#include "query.h"
#include "stack.h"
#include "tracer.h"
#include "whitespace.h"

#include <assert.h>
#include <limits.h>
#include <stdlib.h>

#include <stdio.h> //-

#define M   ( NCORE )



enum n_mode
{
    halted  ,
    running ,
} ;



struct s_ari
{
    struct /* C Z I D B - V N */
    {
        unsigned v : 1 ;
    } ;
    int awake ;
    int done  ;
    enum n_mode mode ;
    //
    byte sun ; // number of data among sup, sub (0, 1, or 2)
    byte sup ; // "super" a.k.a. "top"
    byte sub ; // "sub" a.k.a. "under" or "second"
    byte sex ;
    //
    char * wup ;
    char * wub ;
    char * wex ;
    char   wuu [ HSTR_SIZE_MAX ] ;
    char   wuv [ HSTR_SIZE_MAX ] ;
    //
    //query q ;
    //stack s ; //NOTE [1]
    //stack b ;
} ;
/*  NOTES
 *
 *  [1] each element of mari corresponds with a stack
 *  accessed by the same index.
 *
 */



static
ari * mari [ M ] = { 0 } ;
        // { mari }: "multiple ari"

static
byte m = 0 ;

static
ari * a ;

static
void validate ( void )
{
    assert ( m < M ) ;
    assert ( a ) ;
    assert ( mari [ m ] ) ;
    assert ( a == mari [ m ] ) ;
}



////////



// "A0", "A1", ... , "AE", "AF"
// "B0", "B1", ... , "BE", "BF"
//             ... 
// "P0", "P1", ... , "PE", "PF"
static
void mari_name (
        char h [ static HSTR_SIZE_MAX ] ,
        const byte b )
{
    assert ( b < M ) ;
    hstr_clear ( h ) ;
    h [ 0 ] = 'A' + ( b >> 4 ) ;
    h [ 1 ] = hex_lo ( b ) ;
}



static
void mari_name_1 (
        char h [ static HSTR_SIZE_MAX ] )
{
    mari_name ( h , m ) ;
}



void mari_report_awake ( void )
{
    char h [ HSTR_SIZE_MAX ] ;
    for ( int k = 0 ;  k < M ;  ++ k )
    {
        mari_name ( h , k ) ;
        assert ( 2 == hstr_length ( h ) ) ;
        if ( k ) estream_putx ( ) ;
        else estream_putc ( '_' ) ;
        estream_put_hstr ( h ) ;
    }
    estream_put_guide ( ) ;
    estream_endline ( ) ;
    for ( int k = 0 ;  k < M ;  ++ k )
    {
        const int i = ( k == m )
                ? 2
                : ! ! ( mari [ k ] -> awake ) ;
        const char * const sign [ ] = { " .." , " ::" , " !!" } ;
        estream_puts ( sign [ i ] ) ;
    }
}



static
void mari_switch_to (
        const int i )
{
    m = i % M ;
    a = mari [ m ] ;
    validate ( ) ;
}



////////



static
int stackDump ( void )
{
    return stack_dump ( m ) ;
}

static
int stackLength ( void )
{
    return stack_length ( m ) ;
}



// a { stackPeek } function is not needed (yet) 



static
int stackPull ( void )
{
    return stack_pull ( m ) ;
}

//  return 0 on success; 1 if not.
static
int stackPush (
        const unsigned char u )
{
    TRACER_DECLARE ;
    if ( u == stack_push ( m , u ) ) return 0 ;
    estream_alert ( TRACER , "stack overflow" ) ;
    return a -> v = 1 ;
}

static
void stackReset ( void )
{
    assert ( ! stack_reset ( m ) ) ;
    a -> v = 0 ;
}

static
int stackRoom ( void )
{
    return stack_room ( m ) ;
}



int ari_warm ( void )
{
    TRACER_DECLARE ;
    ////////
    char s [ HSTR_SIZE_MAX ] = "Warm starting core " ;
    char n [ HSTR_SIZE_MAX ] ;
    mari_name_1 ( n ) ;
    assert ( ! hstr_cat ( s , n ) ) ;
    estream_put_warning ( TRACER , s ) ;
    ////////
    validate ( ) ;
    ////////
    stackReset ( ) ;
    query_reset ( ) ;
    hstr_clear ( a -> wuu ) ;
    hstr_clear ( a -> wuv ) ;
    a -> sun = 0 ;
    a -> wup = a -> wex = a -> wuu ;
    a -> wub = a -> wuv ;
    estream_put_note ( TRACER , "Warm restart complete." ) ;
    return 0 ;
}

int ari_cold ( void )
{
    TRACER_DECLARE ;
    ////////
    char s [ HSTR_SIZE_MAX ] = "Cold starting core " ;
    char n [ HSTR_SIZE_MAX ] ;
    mari_name_1 ( n ) ;
    assert ( ! hstr_cat ( s , n ) ) ;
    estream_put_warning ( TRACER , s ) ;
    ////////
    validate ( ) ;
    ////////
    mem_clear ( a , sizeof ( ari ) ) ;
    ari_warm ( ) ;
    return 0 ;
}



////////



static
void mari_reset_initial ( void )
{
    TRACER_DECLARE ;
    static int not_yet_called = 1 ;
    assert ( not_yet_called ) ;
    for ( int i = 0 ;  i < M ;  ++ i )
            if ( ( mari [ i ] = malloc ( sizeof ( ari ) ) ) )
                    mari_switch_to ( i ) ,
                    assert ( ! ari_cold ( ) ) ;
            else
                    estream_put_error ( TRACER , "out of memory" ) ,
                    exit ( EXIT_FAILURE ) ;
    not_yet_called = 0 ;
}



static
void mari_reset_again ( void )
{
    for ( int i = 0 ;  i < M ;  ++ i )
            mari_switch_to ( i ) ,
            assert ( ! ari_cold ( ) ) ;
}



void mari_reset ( void )
{
    static int already_called = 0 ;
    if ( already_called )
            mari_reset_again ( ) ;
    else
            mari_reset_initial ( ) ;
    already_called = 1 ;
}



void mari_unset ( void )
{
    for ( int i = 0 ;  i < M ;  ++ i )
            if ( mari [ i ] ) free ( mari [ i ] ) ;
}


static
int mari_who_is_awake ( void )
{
    for ( int k = 0 ;  k < M ;  ++ k )
    {
        int j = ( m + k ) % M ;
        assert ( mari [ j ] ) ;
        if ( mari [ j ] -> awake ) return j ;
    }
    return -1 ;
}



void mari_rotate ( void )
{
    int i = mari_who_is_awake ( ) ;
    i = i < 0 ? 0 : i ;
    mari_switch_to ( i ) ;
    a -> awake = 1 ;
}



////////



static
void validate_stack_etc ( void )
{
    validate ( ) ;
    assert ( 0 <= a -> sun  &&  a -> sun <= 2 ) ;
    if ( stackLength ( ) )
            assert ( a -> sun == 2 ) ;
}



static
int push (
        const byte x )
{
    TRACER_DECLARE ;
    validate_stack_etc ( ) ;
    if ( 1 < a -> sun )
            { DO ( stackPush , a -> sub ) ; }
    else
            ++ a -> sun ;
    a -> sub = a -> sup ;
    a -> sup = x ;
    return 0 ;
}



////////



int ari_swap ( void )
{
    validate_stack_etc ( ) ;
    if ( 1 < a -> sun )
    {
        a -> sex = a -> sup ;
        a -> sup = a -> sub ;
        a -> sub = a -> sex ;
    }
    else if ( a -> sun )
    {
        a -> sub = a -> sup ;
        a -> sup = 0 ;
        a -> sun = 2 ;
    }
    else ;
    return 0 ;
}



int ari_dup ( void )
{
    TRACER_DECLARE ;
    switch ( a -> sun )
    {
    case 0 :
    {
            a -> sup = 0 ;
            ++ a -> sun ;
    }
    case 1 : return
            a -> sub = a -> sup ,
            ++ a -> sun ,
            0 ;
    case 2 :
    {
            DO ( push , a -> sup ) ;
            return 0 ;
    }
    default :
    {
            assert ( ! "unreachable" ) ;
    }
    }
}



int ari_drop ( void )
{
    validate_stack_etc ( ) ;
    switch ( a -> sun )
    {
    case 2 :
    {
            a -> sup = a -> sub ;
            const int x = stackPull ( ) ;
            if ( x < 0 ) -- a -> sun ;
            else a -> sub = x ;
            return 0 ;
    }
    case 1 :
            a -> sun = a -> sup = 0 ;
    case 0 :
            return 0 ;
    default :
            assert ( ! "unreachable" ) ;
    }
}



int ari_over ( void )
{
    TRACER_DECLARE ;
    switch ( a -> sun )
    {
    case 2 : // ( a b -- b a b )
    {
            DO ( push , a -> sub ) ;
            return 0 ;
    }
    case 0 :
            a -> sup = 0 ;
    case 1 : // ( a -- 0 a 0 )
    {
            a -> sub = 0 ; // ( -- 0 a -- )
            a -> sun = 2 ;
            return ari_over ( ) ;
    }
    default :
            assert ( ! "unreachable" ) ;
    }
}



static
void ari_wswap ( void )
{
    validate ( ) ;
    a -> wex = a -> wup ;
    a -> wup = a -> wub ;
    a -> wub = a -> wex ;
}



static
void ari_wdrop ( void )
{
    validate ( ) ;
    hstr_clear ( a -> wup ) ;
    ari_wswap ( ) ;
}



// ( op-code -- [return-values] )
static
int ari_execute ( void )
{
    if ( a -> sup < 0 ) return ari_nop ( ) ;
    byte opcode = a -> sup ;
    ari_drop ( ) ; // ( -- -- )
    return ( operation_from_opcode ( opcode ) ) ( ) ;
}



int ari_interpret ( void )
{
    TRACER_DECLARE ;
    validate ( ) ;
    DO ( ari_opcode_from_mnemonic ) ;
    // ( -- op-code flag -- )
    if ( ! a -> sup ) ari_wdrop ( ) ;
    ari_drop ( ) ;
    // ( -- op-code -- )
    return ari_execute ( ) ;
}



int ari_nop ( void )
{
    return 0 ;
}



int ari_query ( void )
{
    validate ( ) ;
    ari_wswap ( ) ;
    query_pop ( a -> wup ) ;
    return 0 ;
}



// ( -- op-code flag )
int ari_opcode_from_mnemonic ( void )
{
    TRACER_DECLARE ;
    static int nop = -1 ;
    if ( nop < 0 )
    {
        char h [ HSTR_SIZE_MAX ] ;
        hstr_import ( h , "nop" ) ;
        nop = opcode_from_mnemonic ( h ) ;
        assert ( 0 <= nop  &&  nop <= UCHAR_MAX ) ;
    }
    ////////
    validate ( ) ;
    const int j = opcode_from_mnemonic ( a -> wup ) ;
    const int found = 0 <= j ;
    assert ( j <= UCHAR_MAX ) ;
    DO ( push , ( found ? j : nop ) ) ;
    DO ( push , ( found ? 0 :  -1 ) ) ;
    return 0 ;
}



void ari_stack_dump ( void )
{
    validate_stack_etc ( ) ;
    estream_endline ( ) ;
    estream_puts ( "_SD SR TT SS" ) ;
    estream_put_guide ( ) ;
    estream_endline ( ) ;
    ////////
    {
        int k = stackLength ( ) ;
        int r = stackRoom   ( ) ;
        assert ( 0 <= k  &&  0 <= r ) ;
        //  Stack should never be both empty and full:---
        assert ( k || r ) ;
        estream_dump_byte ( space , k ) ;
        estream_dump_byte ( space , r ) ;
    }
    const char * const none = " -0" ;
    if ( a -> sun )
            estream_dump_byte ( space ,  a -> sup ) ;
    else
            estream_puts ( none ) ;
    if ( a -> sun == 2 )
            estream_dump_byte ( space ,  a -> sub ) ;
    else
            estream_puts ( none ) ;
    stackDump ( ) ;
    estream_endline ( ) ;
}



int ari_zero ( void )
{
    validate_stack_etc ( ) ;
    return
            a -> sun = 2 ,
            a -> sup = a -> sub = 0 ;
}



// Force 
static
void activate_ts ( void )
{
    validate_stack_etc ( ) ;
    switch ( a -> sun )
    {
        case  0 : a -> sup = 0 ,  a -> sun = 1 ;
        case  1 : a -> sub = 0 ,  a -> sun = 2 ;
        default :                              ;
    }
}



int ari_add ( void )
{
    validate_stack_etc ( ) ;
    activate_ts ( ) ;
    const unsigned s = a -> sub  +  a -> sup ;
    a -> sub = s & 0xff ;
    a -> sup = ! ! ( a -> sub < s ) ;
    return 0 ;
}



int ari_nand ( void )
{
    validate_stack_etc ( ) ;
    activate_ts ( ) ;
    a -> sub &=  a -> sup ;
    a -> sup  =  a -> sub  =  ~ a -> sub ;
    return 0 ;
}



void ari_wstack_dump ( void )
{
    estream_endline ( ) ;
    estream_puts ( "_WS" ) ;
    estream_puts ( hstr_length ( a -> wup ) ? " .*" : " ''" ) ;
    estream_puts ( hstr_length ( a -> wub ) ? " .*" : " ''" ) ;
    estream_put_guide ( ) ;
    estream_display_hstr ( a -> wup ) ;
    estream_display_hstr ( a -> wub ) ;
}



int ari_is_awake ( void )
{
    return a -> awake ;
}



static
void wake ( void )
{
    a -> awake = 1 ;
}



int ari_pause ( void )
{
    mari_switch_to ( 0 ) ;
    return 0 ;
}



int ari_sleep ( void )
{
    a -> awake = 0 ;
    return ari_pause ( ) ;
}



int ari_focus ( void )
{
    int t = ( a -> sup < 0 ) ? ( 0 ) : ( a -> sup ) ;
    ari_drop ( ) ;
    mari_switch_to ( t ) ;
    wake ( ) ;
    return 0 ;
}



int ari_mnemonics_dump ( void )
{
    char h [ HSTR_SIZE_MAX ] = { 0 } ;
    for ( int i = 0 ;  i <= UCHAR_MAX ;  ++ i )
            mnemonic_from_opcode ( h , i ) ,
            estream_put_word ( h ) ;
    return 0 ;
}



#undef M
