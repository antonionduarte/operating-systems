#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>

#include "image_ppm.h"

#define TRUE 1
#define FALSE 0

unsigned long primary_colors[RGBV];	// vector to store the sum of intensities for all pixels
unsigned int dominant_primary_color; // dominant/"winner" colour

unsigned char *image; // RGB image read from a file
int width, height; // image dimensions: width is the nº of columns and heigth the nº of lines
int color; // 
int lines_per_thread; // number of lines processed by each thread

pthread_mutex_t ex = PTHREAD_MUTEX_INITIALIZER;	
pthread_barrier_t fillBarrier;

/*
Function that identifies the dominant primary colour, e.g. read, green or blue that
has the biggest contribution to the image and transforms the image to have only
that primary. The calculation of the dominant primary is done by summming all primaries'
contributions to all pixels and finding the biggest value.
*/
void *filter_colors_image(void *id)
{
	int i; // counts the number of pixels
	unsigned long start = 0; // TODO // first pixel to be process
	unsigned long end = 0;  // TODO		
#ifdef VERBOSE
	printf("id = %lu, start = %lu, end= %lu\n", (unsigned long)id, start, end);	
#endif

	unsigned long local_primary_colors[RGBV] = {0, 0, 0};

	// each thread processes its sub-vector
	for(i=start; i < end; i++){
		// TODO
	}

	//All threads communicate to calculate the three sums for all pixels in the image
	// TODO

	// All threads coordinate themselves to identify the dominant primary colour
	// TODO
	
	if( (unsigned long)id == 0 ) {
		#ifdef VERBOSE
		print_primary_intensity( primary_colors );
		#endif
		// dominant_primary_color = TODO
		#ifdef VERBOSE
		printf("dominant_primary_color:%d\n", dominant_primary_color);
		#endif

	}
	
	// TODO

	// All threads filter the non-dominant primary colours in their sub-vectors
	for(i=start; i < end; i++) {
		// TODO
	}
	
	return NULL;
}


/* Parallel transformation of an image withe size nul_cols*num_lines pixels. 
Each thread has to execute the filter() function
*/
void process_image_parallel(int nthreads, unsigned char *input_image, 
			unsigned long num_cols, unsigned long num_lines, void *(*filter)(void *))
{
	pthread_t *ids; // pointer to the vector with the threads' identifiers
	int i;

	image = input_image; // the image to be processed
	width = num_cols; // number of pixels in the yy dimension
	height = num_lines; // number of pixels in the xx dimension

	lines_per_thread = height / nthreads; // number of full lines each thread processes 

	// barrier init
	//TODO
	
	// Thread/worker creation
	//TODO

	// Waits for all threads to conclude
	//TODO

}







