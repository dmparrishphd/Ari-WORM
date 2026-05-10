#ifndef H_CHARSETS
#define H_CHARSETS

#include "byte.h"
#include "dims.h"

void charsets_reset ( void ) ;

extern const char chr_noprint ;

extern const char chr_space ;

char chr_graph (
    const byte ) ;

char chr_print (
    const byte ) ;

#endif
