#include "mem_swap.h"

#include <string.h>

void mem_swap (
        void * const r ,
        void * const s )
{
    unsigned char u ;
    void * const  t = & u ;
    memcpy ( t , r , 1 ) ;
    memcpy ( r , s , 1 ) ;
    memcpy ( s , t , 1 ) ;
}
