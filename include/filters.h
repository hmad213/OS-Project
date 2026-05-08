#ifndef FILTERS_H
#define FILTERS_H

#include "pipeline.h"

const int NUM_FILTERS = 4;
// currently empty. Add whatever filters you like

void filterGrayscale(Image* img);
void filterContrast(Image* img, float factor);
void filterSepia(Image* img);
void filterInvert(Image* img);
void filterFunky(Image* img);
#endif