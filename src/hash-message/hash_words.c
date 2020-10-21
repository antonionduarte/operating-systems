#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
// #include <assert.h>
#include <string.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>

#define MAX_LINE_LEN 256
#define NROT 3

void usage (const char *prog) {
	fprintf (stderr, "Usage (words_hash): %s\n", prog);
	exit (1);
}

// Given a string calculates its hash value
unsigned long hashf (const char *str) {
	unsigned long hash = 0;
	for (int i = 0;  str[i] != '\0';  i++) {
			hash = (hash << (64-NROT)) | (hash >> NROT) | ((unsigned long)str[i] << (64-8));
	}
	return hash;
}

void hash_and_print_words (void) {
	//----------------------------------------
	// Do your stuff here
	//
	// Get words from stdin, one per line, calculate its hash value
	// and print using "printf ("%lu\t%s\n", hash_value, word);"
	//----------------------------------------
}

int main (int argc, char *argv[]) {
	// Check there is one and only one argument
	if (argc != 1) {
			usage (argv[0]);
	}

	hash_and_print_words ();

	exit (0);
}