#include "panel.h"

#include "ari.h"
#include "estream.h"

#include <assert.h>

int panel ( void )
{
    while ( ! 0 )
    {
        if ( ! ari_is_awake ( ) ) mari_rotate ( ) ;
        mari_report_awake ( ) ;
        ari_wstack_dump ( ) ;
        ari_stack_dump ( ) ;
        ari_query ( ) ;
        ari_wstack_dump ( ) ;
        if ( ari_interpret ( ) ) ari_warm ( ) ;
    }
    return 0 ;
}
