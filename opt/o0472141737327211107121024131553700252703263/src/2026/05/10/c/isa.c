#include "isa.h"

#include "ari.h"
#include "byte.h"
#include "hstr.h"
#include "hstr_import.h"
#include "operation.h"

#include <assert.h>
#include <limits.h>
#include <string.h>

struct s_entry
{
    const operation op ;
    const char * const mn ;
    int modes ; // in which modes is the operation valid
} ;

typedef
struct s_entry
entry ;

#define N   ( UCHAR_MAX + 1 )

const entry table [ N ] =
{
    { ari_nop   , "nop"   } ,

    { ari_query , "query" } ,

    { ari_dup   , "dup"   } ,
    { ari_drop  , "drop"  } ,
    { ari_over  , "over"  } ,
    { ari_swap  , "swap"  } ,

    { ari_zero  , "zero"  } ,

    { ari_add   , "add"   } ,
    { ari_nand  , "nand"  } ,

    { ari_sleep , "sleep" } ,
    { ari_pause , "pause" } ,
    { ari_focus , "focus" } ,

    { ari_warm  , "warm"  } ,
    { ari_cold  , "cold"  } ,

    { ari_mnemonics_dump , "mnem" } ,

    { 0 } ,
} ;



operation operation_from_opcode (
        const byte i )
{
    return table [ i ] . op ;
}



void mnemonic_from_opcode (
        char h [ static HSTR_SIZE_MAX ] ,
        const byte i )
{
    assert ( ! hstr_import ( h , table [ i ] . mn ) ) ;
}



int opcode_from_mnemonic (
        const char h [ static HSTR_SIZE_MAX ] )
{
    for ( int i = 0 ;  i < N ;  ++ i )
    {
        const char * const mn = table [ i ] . mn ;
        if ( ! mn                ) return -1 ;
        if ( ! strcmp ( h , mn ) ) return  i ;
    }
    assert ( ! "unreachable" ) ;
}

#undef N
