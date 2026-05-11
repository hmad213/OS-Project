#ifndef PIPELINE_H
#define PIPELINE_H

#define NUMBER_LOADERS 1
#define NUMBER_FILTERS 2
#define NUMBER_ENHANCERS 2
#define NUMBER_SAVERS 3
#define BUFFER_CAPACITY 10
#define BATCH_SIZE 100

#include "buffer.h"
#include <pthread.h>
#include "stages.h"

typedef struct{
    char** paths;
    int index;
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
    
    // All of these are initialized to 0
    int loaderCount;
    int filterCount;
    int enhancerCount;
    int saverCount;

    int loadedCount;
    int filteredCount;
    int enhancedCount;
    int savedCount;

    pthread_mutex_t loaderMutex;
    pthread_mutex_t filterMutex;
    pthread_mutex_t enhancerMutex;
    pthread_mutex_t saverMutex;

    Batch batch;
}Pipeline;

void pipelineInit(Pipeline* p);
void pipelineDestroy(Pipeline* p);
void batchInit(Batch* b, int size);
void batchDestroy(Batch* b);
void runPipeline(Pipeline* p);

#endif