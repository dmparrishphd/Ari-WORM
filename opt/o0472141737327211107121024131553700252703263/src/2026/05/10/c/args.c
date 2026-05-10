#include "args.h"

#include "estream_alert.h"
#include "hstr.h"
#include "hstr_clear.h"
#include "hstr_clean.h"
#include "hstr_copy.h"
#include "hstr_length.h"
#include "is_hstr.h"
#include "parse.h"
#include "tracer.h"

#include <assert.h>
#include <string.h>

#include <stdio.h> //-


/*  args members
 *  a : character data
 *  i : offsets to arguments
 *  k : lengths of arguments
 *  n : number  of arguments
 */


#define N   ( HSTR_SIZE_MAX )
#define M   ( N / 2 )
#define R   ranges [ i ]
static
int import ( 
        byte first  [ static M ] ,
        byte length [ static M ] ,
        const char * const s )
{
    int i = 0 ;
    for ( int cursor = 0 ;   ;  ++ i )
    {
        assert ( i < M ) ;
        size_t r [ 2 ] ;
        parse ( r , s + cursor ) ;
        assert ( r [ 0 ]  <  N ) ;
        assert ( r [ 1 ]  <  N ) ;
        assert ( cursor < N ) ;
        assert ( r [ 0 ]  <  N - cursor ) ;
        assert ( r [ 1 ]  <  N - cursor ) ;
        byte p = r [ 0 ] + cursor ;
        if ( ! s [ p ] ) return i ;
        first [ i ] = p ;
        byte q = r [ 1 ] + cursor ;
        length [ i ] = q - first [ i ] ;    
        if ( ! s [ q ] ) break ;
        cursor = q ;
    }
    return ++ i ;
}
#undef M
#undef N
#undef R



int args_import ( 
        args * const a ,
        const char h [ static HSTR_SIZE_MAX ] )
{
    TRACER_DECLARE ;
    if ( ! a ) return estream_alert (
        TRACER ,
        "Argument 0 is NULL" ) ;
    memset ( a , 0 , sizeof * a ) ;
    if ( ! is_hstr ( h ) )
            return estream_alert (
                TRACER ,
                "Argument 1 is not a short string." ) ;
    a -> n = import ( a -> i , a -> k , h ) ;
    for ( int i = 0 ;  i < a -> n ;  ++ i ) memcpy (
        a -> a + a -> i [ i ] ,
        h +  a -> i [ i ] ,
        a -> k [ i ] ) ;
    return 0 ;
}



const byte args_nmemb (
        const args * const a )
{
    return a ? ( a -> n ) : 0 ;
}



void args_fetch (
        char h [ static HSTR_SIZE_MAX ] ,
        const args * const a ,
        const byte j )
{
    hstr_clear ( h ) ;
    if ( ! a ||  ! a -> n  ||  a -> n <= j ) return ;
    strncpy ( h ,   a -> a  +  a -> i [ j ] ,   a -> k [ j ] ) ;
    hstr_clean ( h ) ;
}
