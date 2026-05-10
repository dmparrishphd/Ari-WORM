#include "query.h"

#include "args.h"
#include "hstr.h"
#include "istream_readline.h"

static int  k = 0 ; // index of next item to pop
static int  n = 0 ; // number of members
static args a = { 0 } ;


void query_reset ( void )
{
    k = n = 0 ;
    const char h [ HSTR_SIZE_MAX ] = { 0 } ;
    args_import ( & a ,  h ) ;
}



static
void refill ( void )
{
    char h [ HSTR_SIZE_MAX ] ;
    istream_readline ( h ) ;
    args_import ( & a ,  h ) ;
    n = args_nmemb ( & a ) ;
    k = 0 ;
}



void query_pop (
        char h [ static HSTR_SIZE_MAX ] )
{
    if ( n <= k ) refill ( ) ;
    args_fetch ( h ,  & a ,  k ++ ) ;
}
