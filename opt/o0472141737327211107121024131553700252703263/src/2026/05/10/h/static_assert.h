#ifndef H_STATIC_ASSERT
#define H_STATIC_ASSERT

#include "enquote.h"

#define STATIC_ASSERT(X) _Static_assert ( X , \
        "file:"  __FILE__ " " \
        "line:" ENQUOTE ( __LINE__ ) )

/*  Mnemonic:---
 *  { _Static_assert } has two underscores and two paramters;
 *  {  STATIC_ASSERT } has one underscore  and one paramter.
 */

#endif
