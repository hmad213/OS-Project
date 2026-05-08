#ifndef FILTERS_H
#define FILTERS_H

#define GRAYSCALE "Grayscale"
#define SEPIA "Sepia"
#define INVERT "Invert"
#define FUNKY "Funky"

#include "pipeline.h"

void filterGrayscale(Image* img);
void filterContrast(Image* img, float factor);
void filterSepia(Image* img);
void filterInvert(Image* img);
void filterFunky(Image* img);
#endif