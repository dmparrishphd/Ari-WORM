#ifndef H_ENQUOTE
#define H_ENQUOTE

#define ENQUOTE_INNER(X)   # X

#define ENQUOTE(X)         ENQUOTE_INNER(X)

#endif
