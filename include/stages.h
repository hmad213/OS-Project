#ifndef STAGES_H
#define STAGES_H

#include "pipeline.h"

void* loader(void* param);
void* filter(void* param);
void* enhancer(void* param);
void* saver(void* param);

#endif