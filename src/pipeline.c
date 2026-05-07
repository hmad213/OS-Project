#include "../include/pipeline.h"
#include <stdlib.h>

#define BUFFER_CAPACITY 10

void batchInit(Batch* b, int size){
    b->count = size;
    b->paths = (char**)malloc(size * sizeof(char*));
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
}

