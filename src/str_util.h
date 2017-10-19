#ifndef STR_UTIL_H
#define STR_UTIL_H
#include "list.h"

char* space_trimmer(char *);
char *trim_spaces(char *);
list *tokenize(const char *, const char *, preprocessor);

#endif /* STR_UTIL_H */
