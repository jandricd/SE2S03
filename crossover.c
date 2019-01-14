// File crossover.c
// David Jandric and Alex Samaha
#include "a4.h"
#include <stdlib.h>

void recombine(Individual *parent1, Individual *parent2, Individual *child1,
               Individual *child2) {

  int image_size = parent1->image.width * parent1->image.height;
  int crossover1 = rand() % image_size / 2;
  int crossover2 = crossover1 + rand() % image_size / 2;
  int i;

  // K-point crossover with k = 2, for more diverse children
  // Children inherit up to crossover1 from the first parent,
  // from crossover1 to crossover2 from the second parent,
  // and from crossover2 to image_size from the first parent
  for (i = 0; i < crossover1; i++) {
    child1->image.data[i] = parent1->image.data[i];
    child2->image.data[i] = parent2->image.data[i];
  }
  for (i = crossover1; i < crossover2; i++) {
    child1->image.data[i] = parent2->image.data[i];
    child2->image.data[i] = parent1->image.data[i];
  }
  for (i = crossover2; i < image_size; i++) {
    child1->image.data[i] = parent1->image.data[i];
    child2->image.data[i] = parent2->image.data[i];
  }
}

void crossover(Individual *population, int population_size) {

  for (int i = 0; i < population_size / 2; i += 2)
    // Parent i and i + 1 produce children population_size / 2 + i and
    // population_size / 2 + i + 1.
    recombine(population + i, population + i + 1,
              population + population_size / 2 + i,
              population + population_size / 2 + i + 1);
}
