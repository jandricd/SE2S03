// File population.c
// David Jandric and Alex Samaha
#include "a4.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX max_color + 1

PIXEL *generate_random_image(int width, int height, int max_color) {
  
  PIXEL *pixels = malloc(sizeof(PIXEL) * width * height);
  PIXEL *p = pixels;
  int i;

  // Initializing each pixel with random RGB values up to 255
  for (i = 0; i < height * width; i++) {
    pixels[i].r = (unsigned char)(rand() % (MAX));
    pixels[i].g = (unsigned char)(rand() % (MAX));
    pixels[i].b = (unsigned char)(rand() % (MAX));
  }
  return p;
}

Individual *generate_population(int population_size, int width, int height,
                                int max_color) {

  Individual *population = malloc(sizeof(Individual) * population_size);
  int i;
  // Generating images for each individual in population
  for (i = 0; i < population_size; i++) {
    population[i].image.data = generate_random_image(width, height, max_color);
    population[i].image.width = width;
    population[i].image.height = height;
    population[i].image.max_color = max_color;
  }
  return population;
}
