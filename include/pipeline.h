#ifndef PIPELINE_H
#define PIPELINE_H

#define NUMBER_LOADERS 2
#define NUMBER_FILTERS 3
#define NUMBER_ENHANCERS 3
#define NUMBER_SAVERS 2

#include "buffer.h"

typedef struct{
    char** paths;
    int count;
}Batch;

typedef struct Pipeline{
    Buffer loaded;
    Buffer filtered;
    Buffer enhanced;
    
    pthread_t loader[NUMBER_LOADERS];
    pthread_t filter[NUMBER_FILTERS];
    pthread_t enhancer[NUMBER_ENHANCERS];
    pthread_t saver[NUMBER_SAVERS];

    char* filterName;
    char* enhancerName;

    Batch batch;
};

#endif