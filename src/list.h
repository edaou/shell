#ifndef LIST
#define LIST

typedef struct list list;
struct list {
  void *data;
  list *next;
};

typedef unsigned long size_t;

typedef char* (*preprocessor)(char*);

list *list_add(list*, void*);
size_t list_size(list*);
list *list_new(void*);
char **to_array(list*);
#endif /* LIST */
