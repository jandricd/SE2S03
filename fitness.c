// File fitness.c
// David Jandric and Alex Samaha
#include "a4.h"
#include <math.h>
#include <stdio.h>

#define SQR(x) (x) * (x)

double comp_distance(const PIXEL *A, const PIXEL *B, int image_size) {
  int i;
  double distance = 0;
  double differenceR = 0, differenceG = 0, differenceB = 0;

  // Calculate distance between pixels using distance formula applied to each
  // component of pixels, split up for optimization
  for (i = 0; i < image_size; i++) {
    differenceR = (A + i)->r - (B + i)->r;
    differenceG = (A + i)->g - (B + i)->g;
    differenceB = (A + i)->b - (B + i)->b;
    differenceR = SQR(differenceR);
    differenceG = SQR(differenceG);
    differenceB = SQR(differenceB);
    distance += differenceR + differenceG + differenceB;
  }

  distance = sqrt(distance);
  return distance;
}

void comp_fitness_population(const PIXEL *image, Individual *individual,
                             int population_size) {

  // Calculating the fitness for each individual in the population
  int i;
  Individual *p = individual;
  for (i = 0; i < population_size; i++) {
    p->fitness =
        comp_distance(image, p->image.data, p->image.width * p->image.height);
    p++;
  }
}
