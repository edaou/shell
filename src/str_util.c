#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "str_util.h"

char* space_trimmer(char *);
char* identity(char*);


char *trim_spaces(char *s) {
  size_t n;
  if (s == NULL || (n = strlen(s)) == 0) {
    return s;
  }

  size_t start_spaces = 0, end_spaces = 0;

  for (; start_spaces < n && isspace(s[start_spaces]); start_spaces++);
  for (int i = n-1; i >= 0 && isspace(s[i]); i--, end_spaces++);

  int trimmed_n = n - start_spaces - end_spaces;
  char *trimmed = malloc(sizeof(char) * (trimmed_n + 1));

  for (size_t i = start_spaces; i < n - end_spaces; i++) {
    trimmed[i - start_spaces] = s[i];
  }
  trimmed[trimmed_n] = '\0';
  return trimmed;
}

list *tokenize(const char *cmd, const char *delim, preprocessor passed_preprocessor) {
  const preprocessor preprocess = (passed_preprocessor == NULL) ? identity : passed_preprocessor;
  char *processed_arg = NULL,
    *remaining = strdup(cmd),
    *arg = strtok_r(remaining, delim, &remaining);

  list *l = list_new(arg), *p = l;
  while ((arg = strtok_r(remaining, delim, &remaining)) != NULL) {
    processed_arg = preprocess(arg);
    if (processed_arg != NULL) {
      p = list_add(p, processed_arg);
    }

  }
  return l;
}

char* space_trimmer(char *s) {
  char *processed_arg;
  if ((processed_arg = trim_spaces(s)) != NULL && strlen(processed_arg) > 0) {
    return processed_arg;
  }
  return NULL;
}

char* identity(char *s) {
  return s;
}
