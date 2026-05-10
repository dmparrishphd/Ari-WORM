#include "mem_rev.h"

#include "mem_swap.h"

#include <stddef.h>

void mem_rev (
        void * p ,
        size_t n )
{
    const size_t m = n >> 1 ;
    for ( size_t k = 0 ;  k < m ;  ++ k )
            mem_swap ( p + k , p + n - 1 - k ) ;
}
