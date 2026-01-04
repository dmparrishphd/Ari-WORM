#include "sighnd_int.h"

#include <signal.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>

#define ENABLE \
        ( SIG_ERR != signal ( SIGINT , sigint_accept ) )

#define DISABLE \
        ( SIG_ERR != signal ( SIGINT , SIG_IGN       ) )

sig_atomic_t attention_requested = 0 ;

_Static_assert (
    atomic_is_lock_free ( & attention_requested ) ,
    "" ) ;

int sigint_pending ( void )
{
    return ! ! attention_requested ;
}



/*  The sigint_accept function
 *
 *  In order to avoid undefined behavior, the only
 *  functions called are { signal } and { _Exit }
 *  and the only object referenced is
 *  attention_requested (a lock-free atomic object)
 *  (N2176 7.14.1.1-5).
 *    First, the { signal } function is called via
 *  DISABLE to avoid implementation-defined behavior
 *  (N2176 7.14.1.1-3).
 */
static
void sigint_accept (
        int n )
{
    if ( DISABLE )
            attention_requested = 1 ;
    else
            _Exit ( EXIT_FAILURE ) ;
}



static
void eputs (
        const char * const s )
{
    if ( fputs ( s , stderr ) < 0 )
            exit ( EXIT_FAILURE ) ;
}



#define RESPONSE   "response to interactive attention signal"
#define PROMPT     "\n\n" \
        "*  Beginning " RESPONSE ".\n" \
        "*  Press Enter to continue. Enter something else to end program. "
void sigint_respond ( void )
{
    if ( ! DISABLE ) exit ( EXIT_FAILURE ) ;
    if ( attention_requested )
    {
        eputs ( PROMPT ) ;
        clearerr ( stdin ) ;
        if ( '\n' != getchar ( ) ) exit (
            ferror ( stdin ) ? EXIT_FAILURE : EXIT_SUCCESS ) ;
        eputs ( "*  Ending " RESPONSE ".\n\n" ) ;
    }
    attention_requested = 0 ;
    if ( ! ENABLE ) exit ( EXIT_FAILURE ) ;
}
#undef PROMPT
#undef RESPONSE
