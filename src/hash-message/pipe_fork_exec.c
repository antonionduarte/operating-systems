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
      close(stdin);
      dup(fd[0]);
      close(fd[1]);
      close(fd[0]);
      execv("hash_words", NULL);
      break;
    default: // parent process (executes split_words)
      close(stdout);
      dup(fd[1]);
      close(fd[1]);
      close(fd[0]);
      execv("split_words", argv);
      break;
  }

  //----------------------------------------
  // Do your stuff here
  //
  // create pipe, fork and redirect I/O to/from pipe,
  // parent execs one of "split_words" or "hash_words" 
  // and the child execs the other one
  //----------------------------------------
  
  exit (0);
}