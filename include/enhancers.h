#ifndef ENHANCERS_H
#define ENHANCERS_H

#include "pipeline.h"

#define WARMTH "Warmth"
#define BRIGHTEN "Brighten"
#define CONTRAST "Contrast"
#define SHARPEN "Sharpen"
#define SATURATE "Saturate"

void* warmth(Image *img);
void* brighten(Image *img);
void* contrast(Image *img);
void* sharpen(Image *img);
void* saturate(Image *img);

#endif