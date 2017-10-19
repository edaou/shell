#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "shell.h"
#include "list.h"
#include "str_util.h"

void run_cmd(char *cmd, int read_fd, int write_fd);

void execseq(list *cmds) {
  int (*pipes)[2];
  size_t
    num_cmds = list_size(cmds),
    num_pipes = num_cmds - 1,
    i;

  pipes = malloc(sizeof(*pipes) * num_pipes);

  for (i = 0 ; i < num_pipes; i++) {
    if (pipe(pipes[i]) < 0) {
      perror("pipe");
      exit(EXIT_FAILURE);
    }
  }

  list *p = cmds;
  for (i = 0; i < num_cmds; i++, p = p->next) {
    if (i == 0) {
      run_cmd(p->data, 0, pipes[i][1]);
    } else if (i == num_pipes) {
      run_cmd(p->data, pipes[i-1][0], 0);
    } else {
      run_cmd(p->data, pipes[i-1][0], pipes[i][1]);
    }
  }
}

void run_cmd(char *cmd, int read_fd, int write_fd) {
  pid_t pid;
  int status;

  if ((pid = fork()) < 0) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (pid) {
    if (read_fd) {
      if (close(read_fd) < -1) {
        perror("close");
        exit(EXIT_FAILURE);
      }
    }

    if (write_fd) {
      if (close(write_fd) < -1) {
        perror("close");
        exit(EXIT_FAILURE);
      }
    }
    if (waitpid(pid, &status, 0) < 0) {
      perror("waitpid");
      exit(EXIT_FAILURE);
    }
    return;
  }

  if (read_fd) {
    dup2(read_fd, 0);
  }

  if (write_fd) {
    dup2(write_fd, 1);
  }

  char **args = to_array(tokenize(cmd, "  \n\t", space_trimmer));
  execvp(args[0], args);
}
