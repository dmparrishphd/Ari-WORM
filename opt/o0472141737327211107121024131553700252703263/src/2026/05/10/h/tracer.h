#ifndef H_TRACER
#define H_TRACER

#include "enquote.h"

struct s_tracer
{
    const char * func ;
    const char * file ;
    const char * line ;
} ;

typedef
struct s_tracer
tracer ;

#define TRACER_DECLARE \
        ; tracer theTracer = { __func__ , __FILE__ } ;

#define TRACER \
        ( ( theTracer . line = ENQUOTE ( __LINE__ ) ) , \
        ( & theTracer ) )

#endif
