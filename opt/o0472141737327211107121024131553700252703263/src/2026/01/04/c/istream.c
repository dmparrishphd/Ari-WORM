#include "istream.h"

#include <stdio.h>



int istream_error ( void )
{
    return ! ! ferror ( stdin ) ;
}



int istream_eof ( void )
{
    return ! ! feof ( stdin ) ;
}
