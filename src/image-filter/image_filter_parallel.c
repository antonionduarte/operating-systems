#define _POSIX_C_SOURCE 200112L // added this define so that VSCode identifies pthread_barriers 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#ifdef __APPLE__
	#include "../pthread-barrier/pthread_barrier.c" // added this so it works on macOS
#endif

#include "image_ppm.h"

#define TRUE 1
#define FALSE 0

unsigned long primary_colors[RGBV];   // vector to store the sum of intensities for all pixels
unsigned int dominant_primary_color;  // dominant/"winner" colour

unsigned char *image;  // RGB image read from a file
int width, height;     // image dimensions: width is the nº of columns and heigth the nº of lines
int color;             //
int lines_per_thread;  // number of lines processed by each thread

pthread_mutex_t ex = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t fillBarrier;

/**
 * Function that identifies the dominant primary colour, e.g. read, green or blue that
 * has the biggest contribution to the image and transforms the image to have only
 * that primary. The calculation of the dominant primary is done by summming all primaries'
 * contributions to all pixels and finding the biggest value.
*/
void *filter_colors_image(void *id) {
  int i;                    // counts the number of pixels
  unsigned long start = (long) id * lines_per_thread * width * RGBV; // first pixel to be process
  unsigned long end = (long) (id + 1) * lines_per_thread * width * RGBV - 1; // last pixel to process 
	#ifdef VERBOSE
		printf("id = %lu, start = %lu, end= %lu\n", (unsigned long)id, start, end);
	#endif

  unsigned long local_primary_colors[RGBV] = {0, 0, 0};

  // each thread processes its sub-vector
  for (i = start; i < end; i += 3) {
		local_primary_colors[RED] += image[i]; 
		local_primary_colors[GREEN] += image[i + 1];
		local_primary_colors[BLUE] += image[i + 2];
  }

  // all threads communicate to calculate the three sums for all pixels in the image
	pthread_mutex_lock(&ex);
		primary_colors[RED] += local_primary_colors[RED];
		primary_colors[GREEN] += local_primary_colors[GREEN];
		primary_colors[BLUE] += local_primary_colors[BLUE]; 
	pthread_mutex_unlock(&ex);

	// waits for all threads to get here before continuing
	pthread_barrier_wait(&fillBarrier);

  // all threads coordinate themselves to identify the dominant primary colour
	if ((unsigned long) id == 0) {
		#ifdef VERBOSE
			print_primary_intensity(primary_colors);
		#endif

		dominant_primary_color = compare_colors(primary_colors);
		
		#ifdef VERBOSE
			printf("dominant_primary_color:%d\n", dominant_primary_color);
		#endif
	}

	// waits for all threads to get here before continuing
	pthread_barrier_wait(&fillBarrier);

  // all threads filter the non-dominant primary colours in their sub-vectors
	for (i = start; i < end; i += 3) {
		filter_colors(&image[i], dominant_primary_color);
  }

  return NULL;
}

/** 
 * Parallel transformation of an image withe size nul_cols*num_lines pixels. 
 * Each thread has to execute the filter() function
*/
void process_image_parallel(int nthreads, unsigned char *input_image,
                            unsigned long num_cols, unsigned long num_lines, void *(*filter)(void *)) {
  pthread_t *ids;  // pointer to the vector with the threads' identifiers

  image = input_image;  // the image to be processed
  width = num_cols;     // number of pixels in the yy dimension
  height = num_lines;   // number of pixels in the xx dimension

  lines_per_thread = height / nthreads;  // number of full lines each thread processes

  // barrier init
  pthread_barrier_init(&fillBarrier, NULL, nthreads);

	// reservates space for the ids
	ids = malloc(sizeof(unsigned long) * nthreads);

	// initializes the ids
	for (int i = 0; i < nthreads; i++) {
		ids[i] = i; 
	}

	// create the threads
  for (int i = 0; i < nthreads; i++) {
		pthread_create(&ids[i], NULL, filter_colors_image, (void*) ids[i]);
	}

  // waits for all threads to conclude
  for (int i = 0; i < nthreads; i++) {
		pthread_join(ids[i], NULL);
	}
}
