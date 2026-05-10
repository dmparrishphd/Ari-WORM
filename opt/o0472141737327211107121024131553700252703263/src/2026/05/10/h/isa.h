#ifndef H_ISA
#define H_ISA

#include "byte.h"
#include "hstr.h"
#include "operation.h"

operation operation_from_opcode (
    const byte ) ;

void mnemonic_from_opcode (
    char [ static HSTR_SIZE_MAX ] ,
    const byte i ) ;

int opcode_from_mnemonic (
    const char [ static HSTR_SIZE_MAX ] ) ;

#endif
