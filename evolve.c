// File evolve.c
// David Jandric and Alex Samaha
#include "a4.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int comparison(const void *a, const void *b) {
  if (((const Individual *)a)->fitness > ((const Individual *)b)->fitness)
    return 1;
  else if (((const Individual *)a)->fitness == ((const Individual *)b)->fitness)
    return 0;
  else
    return -1;
}

PPM_IMAGE *evolve_image(const PPM_IMAGE *image, int num_generations,
                        int population_size, double rate) {

  srand(time(NULL));
  // Generating random population of size population_size
  Individual *population = generate_population(population_size, image->width,
                                               image->height, image->max_color);

  // Computing initial fitness of individuals in population
  comp_fitness_population(image->data, population, population_size);
  qsort(population, population_size, sizeof(Individual), comparison);
  double difference = 0;
  double previous = population[0].fitness;

  // Mutating the population with an adjusted rate, computing fitness of individuals and sorting
  // individuals by fitness
  int i, j;
  double adjustedRate = rate;
  for (i = 0; i < num_generations; i++) {
    adjustedRate = (10 * rate) * exp(-i / 10000) + rate;
    crossover(population, population_size);
    mutate_population(population, population_size, adjustedRate);
    comp_fitness_population(image->data, population, population_size);
    qsort(population, population_size, sizeof(Individual), comparison);
    difference = population[0].fitness - previous;
    previous = population[0].fitness;

    // This code is for creating a video, if desired
    // const char g[32];
    // if (i%100 == 0){
    //   sprintf(g, "video%d.ppm", i);
    //
    //   write_ppm (g, &population[0].image);
    // }

    printf("%-8d   %.3f   %8.3f\n", i + 1, population[0].fitness, difference);
  }

  // Copying the best image and its data from the population
  PPM_IMAGE *goodImage = malloc(sizeof(PPM_IMAGE));
  goodImage->width = population[0].image.width;
  goodImage->height = population[0].image.height;
  goodImage->max_color = population[0].image.max_color;
  goodImage->data = population[0].image.data;

  // Freeing all the data from population, except first individual
  for (j = 1; j < population_size; j++) {
    free(population[j].image.data);
  }
  free(population);

  // Returning the best image
  printf("\aFinished!\n");
  return goodImage;
}

// Frees PPM_IMAGE structure
void free_image(PPM_IMAGE *p) {
  if (p->data != NULL)
    free(p->data);
  free(p);
  return;
}
