#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "image_filter_parallel.h"
#include "image_ppm.h"

int main(int argc, char *argv[]) {
  int nthreads;
  unsigned char *image;  // RGB image read from a file
  int width, height;     // image dimensions: width is the nº of columns and heigth the nº of lines
  int colour;            // maximum number of colour intensity in the image

  if (argc != 4) {
    printf("Usage: %s input_file output_file nthreads\n", argv[0]);
    return 1;
  }

  // read original image
  input_ppm(argv[1], &width, &height, &colour, &image);

  if (((nthreads = atoi(argv[3])) <= 0) || (height % nthreads) != 0) {
    printf("Number of threads must be positive and multiple of the image's lines\n");
    printf("nthreads:%d width:%d height:%d height %% nthreads:%d\n",
           nthreads, width, height, height % nthreads);
    exit(0);
  }

  // transforms image
  process_image_parallel(nthreads, image, width, height, filter_colors_image);

  // writes processed image
  output_ppm(argv[2], width, height, colour, image);

  return 0;
}
