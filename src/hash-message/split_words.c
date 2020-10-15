#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_LINE_LEN 256

void usage (const char *prog) {
    fprintf (stderr, "Usage (words): %s [file_path]\n", prog);
    exit (1);
}

void split_print_words (const char *filename) {
    FILE *fd = stdin;  // By default will read from stdin
    if (filename != NULL && strcmp (filename, "-") != 0) {
        // A file name was given, let's open it to read from there
        fd = fopen (filename, "r");
        assert (fd != NULL);
    }

    //----------------------------------------
    // Do your stuff here
    //
    // Get a line from the file stream "fd", split it into words,  
    // and print those words
    // Most of the code you need here can be reused from the "shell" lab
    // work, such as "makeargv" and a while loop reading with "fgets"
    //----------------------------------------
}

int main (int argc, char *argv[]) {
    // Check there is one and only one argument
    if (argc < 1 || argc > 2) {
        usage (argv[0]);
    }

    split_print_words (argv[1]);

    exit (0);
}