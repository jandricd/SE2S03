// File mutate.c
// David Jandric and Alex Samaha
#include "a4.h"
#include <stdlib.h>

#define SIZE individual->image.height * individual->image.width
#define MAX individual->image.max_color + 1

void mutate(Individual *individual, double rate) {

  int i, pixel;
  rate = rate > 100 ? 100 : rate;

  // m represents the number of pixels to mutate in the individuals image
  int m = (int)(rate / 100 * SIZE);
  for (i = 0; i < m; i++) {
    pixel = rand() % (SIZE);
    individual->image.data[pixel].r = rand() % (MAX);
    individual->image.data[pixel].g = rand() % (MAX);
    individual->image.data[pixel].b = rand() % (MAX);
  }
}

void mutate_population(Individual *individual, int population_size,
                       double rate) {

  // Mutate all but 2 of the best individuals
  // Changed for sake of mutating more individuals for a more diverse population
  // but leaving the 2 best parents
  int i;
  for (i = 2; i < population_size; i++) {
    mutate(individual + i, rate);
  }
}
