#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void usage (const char *prog) {
  printf ("Usages: %s [file_path]\n", prog);
    exit (1);
}

int main (int argc, char *argv[]) {
  // Check there is one and only one argument
  if (argc < 1 || argc > 2) {
    usage (argv[0]);
  }

  int pid = fork(); // fork of parent process
  int fd[2]; // array with read and write extremities of pipe
  pipe(fd); // create the communication pipe
  
  switch (pid) {
    case -1: // error
      perror("fork");
      exit(1);
      break;
    case 0: // child process (executes hash_words)
      close(0);
      dup(fd[0]);
      close(fd[0]);
      close(fd[1]);
      char* args[] = {"./hash_words", NULL};
      execv("./hash_words", args);
      break;
    default: // parent process (executes split_words)
      close(1);
      dup(fd[1]);
      close(fd[1]);
      close(fd[0]);
      char* args2[] = {"./split_words", argv[1], NULL};
      execv("./split_words", args2);
      break;
  }

  exit (0);
}