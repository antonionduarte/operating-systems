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

    //----------------------------------------
    // Do your stuff here
    //
    // create pipe, fork and redirect I/O to/from pipe,
    // parent execs one of "split_words" or "hash_words" 
    // and the child execs the other one
    //----------------------------------------
    
    exit (0);
}