#include "../include/stages.h"

void* loader(void* param){
    Pipeline* p = param;

    while(1){
        pthread_mutex_lock(&p->loaderMutex);
        int i = p->loaderCount++;
        pthread_mutex_unlock(&p->loaderMutex);

        if(i > p->batch.count){
            break;
        }

        Image img = LoadImage(p->batch.paths[i]);
        if(img.data == NULL){
            continue;
        }

        bufferPush(&p->loaded, img);
    }

    pthread_exit(NULL);
}