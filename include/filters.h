#ifndef FILTERS_H
#define FILTERS_H

#include "pipeline.h"

void filterGrayscale(Image* img);
void filterContrast(Image* img, float factor);
void filterSepia(Image* img);
void filterInvert(Image* img);
void filterFunky(Image* img);
#endif