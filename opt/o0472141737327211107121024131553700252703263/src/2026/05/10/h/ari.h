#ifndef H_ARI
#define H_ARI

#include "byte.h"
#include "operation.h"

typedef
struct s_ari
ari ;

int ari_is_awake ( void ) ;

////////

void mari_reset ( void ) ;

void mari_unset ( void ) ;

void mari_report_awake ( void ) ;

void mari_rotate ( void ) ;

////////

void ari_stack_dump ( void ) ;

void ari_wstack_dump ( void ) ;

int ari_interpret ( void ) ;

int ari_opcode_from_mnemonic ( void ) ;

////////

int ari_nop   ( void ) ;

int ari_query ( void ) ;

int ari_dup   ( void ) ;

int ari_drop  ( void ) ;

int ari_over  ( void ) ;

int ari_swap  ( void ) ;

int ari_zero  ( void ) ;

int ari_add   ( void ) ;

int ari_nand  ( void ) ;

int ari_sleep ( void ) ;

int ari_pause ( void ) ;

int ari_focus ( void ) ;

int ari_warm  ( void ) ;

int ari_cold  ( void ) ;

int ari_mnemonics_dump ( void ) ;

#endif
