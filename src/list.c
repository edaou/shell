#include <stdlib.h>
#include "list.h"

list *list_add(list *p, void *data) {
  list *l = malloc(sizeof(list));
  l->data = data;
  l->next = NULL;
  p->next = l;
  return l;
}

size_t list_size(list* l) {
  size_t n = 0;
  for (list *current = l; current != NULL; current = current->next, n++);
  return n;
}

list *list_new(void *data) {
  list *l = malloc(sizeof(list));
  l->next = NULL;
  l->data = data;
  return l;
}

char **to_array(list *l) {
  size_t n = list_size(l);
  char **args = malloc((n + 1) * sizeof(char*));
  list *p = l;
  for (size_t i = 0; i < n; i++, p=p->next) {
    args[i] = (char*)p->data;
  }
  args[n] = NULL;
  return args;
}
