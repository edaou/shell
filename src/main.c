#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "shell.h"
#include "str_util.h"

int main(void) {
  char shell_prompt[100], *line = NULL;
  rl_bind_key('\t', rl_complete);
  while(1) {
    snprintf(shell_prompt, sizeof(shell_prompt), "%s:%s $ ", getenv("USER"), getcwd(NULL, 1024));
    if (!(line = readline(shell_prompt))) {
      break;
    }
    add_history(line);
    execseq(tokenize(line, "|", space_trimmer));
    free(line);
  }
  exit(EXIT_SUCCESS);
}
