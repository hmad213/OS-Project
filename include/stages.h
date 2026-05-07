#ifndef STAGES_H
#define STAGES_H

#include "pipeline.h"
#include "enhancers.h"
#include "filters.h"
#include <string.h>

void* loader(void* param);
void* filter(void* param);
void* enhancer(void* param);
void* saver(void* param);

void applyEnhancement(Image *img, const char* type);

#endif