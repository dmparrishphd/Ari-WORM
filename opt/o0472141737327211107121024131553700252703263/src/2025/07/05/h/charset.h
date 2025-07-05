#ifndef H_CHARSET
#define H_CHARSET

#include <limits.h>

#define CHARSET_NMEMB   ( 1 + UCHAR_MAX )
        //  One element for each value of { unsigned char }.
#define CHARSET_SIZE    ( CHARSET_NMEMB + 1 )
        //  "+ 1": One element for a TNC.

_Static_assert ( CHAR_BIT == 8 ,  "" ) ;
        /*  therefore:
         *      -   UCHAR_MAX    == 255
         *      -   CHARSET_SIZE == 257 < INT_MAX
         */

#endif
