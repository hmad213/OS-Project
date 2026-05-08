#include "../include/pipeline.h"
#include <stdlib.h>


void batchInit(Batch* b, int size){
    b->count = size;
    b->paths = (char**)malloc(size * sizeof(char*));
    b->index = 0;
    for(int i = 0; i < size; i++){
        b->paths[i] = NULL; 
    }
}

void batchDestroy(Batch* b){
    if(b->paths != NULL){
        free(b->paths);
        b->paths = NULL;
    }
    b->count = 0;
    b->index = 0;
}

void pipelineInit(Pipeline* p){
    bufferInit(&p->loaded, BUFFER_CAPACITY);
    bufferInit(&p->filtered, BUFFER_CAPACITY);
    bufferInit(&p->enhanced, BUFFER_CAPACITY);

    batchInit(&p->batch, BATCH_SIZE);

    p->filterName = "";
    p->enhancerName = "";

    p->loaderCount = 0;
    p->filterCount = 0;
    p->enhancerCount = 0;
    p->saverCount = 0;

    p->loadedCount = 0;
    p->filteredCount = 0;
    p->enhancedCount = 0;
    p->savedCount = 0;

    pthread_mutex_init(&p->loaderMutex, NULL);
    pthread_mutex_init(&p->filterMutex, NULL);
    pthread_mutex_init(&p->enhancerMutex, NULL);
    pthread_mutex_init(&p->saverMutex, NULL);
}

void pipelineDestroy(Pipeline* p){
    bufferDestroy(&p->loaded);
    bufferDestroy(&p->filtered);
    bufferDestroy(&p->enhanced);

    batchDestroy(&p->batch);

    pthread_mutex_destroy(&p->loaderMutex);
    pthread_mutex_destroy(&p->filterMutex);
    pthread_mutex_destroy(&p->enhancerMutex);
    pthread_mutex_destroy(&p->saverMutex);
}

void runPipeline(Pipeline* p){
    for(int i = 0; i < NUMBER_LOADERS; i++){
        pthread_create(&p->loader[i], NULL, loader, p);
    }
    for(int i = 0; i < NUMBER_ENHANCERS; i++){
        pthread_create(&p->enhancer[i], NULL, enhancer, p);
    }
    for(int i = 0; i < NUMBER_FILTERS; i++){
        pthread_create(&p->filter[i], NULL, filter, p);
    }
    for(int i = 0; i < NUMBER_SAVERS; i++){
        pthread_create(&p->saver[i], NULL, saver, p);
    }
}