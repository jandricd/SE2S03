// File readwriteppm.c
// David Jandric and Alex Samaha
#include "a4.h"
#include <stdio.h>
#include <stdlib.h>

// Certain lines pulled from this stack overflow post:
// https://stackoverflow.com/questions/2693631/read-ppm-file-and-store-it-in-an-array-coded-with-c
PPM_IMAGE *read_ppm(const char *file_name) {

  // Input image processing
  FILE *f = fopen(file_name, "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open %s\n", file_name);
    fclose(f);
    exit(1);
  }
  printf("Opened %s\n", file_name);

  char temp[2];
  fscanf(f, "%c%c", &temp[0], &temp[1]);
  if (temp[0] != 'P' && temp[1] != '3') {
    printf("Wrong image format\n");
    fclose(f);
    exit(1);
  }
  printf("Correct image format\n");

  PPM_IMAGE *ogImage = malloc(sizeof(PPM_IMAGE));
  ogImage->data = malloc(ogImage->width * ogImage->height * sizeof(PIXEL));

  fscanf(f, "%d %d", (int *)(&ogImage->width), (int *)(&ogImage->height));
  fscanf(f, "%d", (int *)(&ogImage->max_color));
  while (fgetc(f) != '\n')
    ;

  int i;
  for (i = 0; i < ogImage->width * ogImage->height; i++)
    fscanf(f, "%hhu %hhu %hhu", &(ogImage->data[i].r), &(ogImage->data[i].g),
           &(ogImage->data[i].b));

  fclose(f);
  printf("Closed file %s, read succesful\n", file_name);
  return ogImage;
}

void write_ppm(const char *file_name, const PPM_IMAGE *image) {

  FILE *p = fopen(file_name, "w");
  int i;

  fprintf(p, "P3\n");
  fprintf(p, "%d %d\n", image->width, image->height);
  fprintf(p, "%d\n", image->max_color);
  for (i = 0; i < image->width * image->height; i++) {
    fprintf(p, "%d %d %d ", image->data[i].r, image->data[i].g,
            image->data[i].b);
  }
  fclose(p);
}
