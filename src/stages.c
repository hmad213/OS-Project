#include "../include/stages.h"

void* loader(void* param){
    Pipeline* p = param;

    while(1){
        pthread_mutex_lock(&p->loaderMutex);
        int i = p->loaderCount++;
        pthread_mutex_unlock(&p->loaderMutex);

        if(i >= p->batch.count){
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


void* filter(void* param){
    Pipeline *p = param;

    while(1){
        pthread_mutex_lock(&p->filterMutex);
        int i= p->filterCount++;
        pthread_mutex_unlock(&p->filterMutex);

        if(i >= p->batch.count){
            break;
        }
        Image img = bufferPop(&p->loaded);

        if(strcmp(p->filterName , "grascale") == 0){
            ImageColorGrayscale(&img);
        } else if(strcmp(p->filterName , "contrast") == 0){
            ImageColorContrast(&img , 40.0f);
        } else if(strcmp(p->filterName , "blur") == 0){
            ImageBlurGaussian(&img , 4);
        }
        bufferPush(&p->filtered , img);
    }
    pthread_exit(NULL);
}

void* applyEnhancement(Image *img, const char *type){
    if(type == NULL || img->data == NULL) return;

    if(strcmp(type, "Warmth") == 0){
        warmth(&img);
    }
    else if(strcmp(type, "Brighten") == 0){
        brighten(&img);
    }
    else if(strcmp(type, "Contrast") == 0){
        contrast(&img);
    }
    else if(strcmp(type, "Sharpen") == 0){
        sharpen(&img);
    }
    else if(strcmp(type, "Saturate") == 0){
        saturate(&img);
    }
}

void* enhancer(void* param){
    Pipeline* p = param;

    while(1){
        pthread_mutex_lock(&p->enhancerMutex);
        int i = p->enhancerCount++;
        pthread_mutex_unlock(&p->enhancerMutex);

        if(i >= p->batch.count){
            break;
        }

        Image img = bufferPop(&p->filtered);
        if(img.data == NULL){
            continue;
        }

        applyEnhancement(&img, p->enhancerName);

        bufferPush(&p->enhanced, img);
    }

    pthread_exit(NULL);
}