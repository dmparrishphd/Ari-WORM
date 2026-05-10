#ifndef H_ARGS
#define H_ARGS

#include "byte.h"
#include "hstr.h"

struct s_args
{
    char a [ HSTR_SIZE_MAX     ] ;
    byte i [ HSTR_SIZE_MAX / 2 ] ;
    byte k [ HSTR_SIZE_MAX / 2 ] ;
    byte n ;
} ;

typedef
struct s_args
args ;

int args_import (
    args * const ,
    const char [ static HSTR_SIZE_MAX ] ) ;

const byte args_nmemb (
    const args * const ) ;

void args_fetch (
    char [ static HSTR_SIZE_MAX ] ,
    const args * const ,
    const byte ) ;

#endif
