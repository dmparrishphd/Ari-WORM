#ifndef H_TRACE
#define H_TRACE

#define TRACE2(X)   # X

#define TRACE1(X)   TRACE2(X)

#define TRACE        __FILE__ , TRACE1(__LINE__) ,  __func__

#endif
