#ifndef ENHANCERS_H
#define ENHANCERS_H

#include "pipeline.h"

const int NUM_ENHANCERS = 5;

void* warmth(Image *img);
void* brighten(Image *img);
void* contrast(Image *img);
void* sharpen(Image *img);
void* saturate(Image *img);

#endif