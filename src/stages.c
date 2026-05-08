#include "../include/stages.h"

void* loader(void* param){
    Pipeline* p = param;

    while(1){
        pthread_mutex_lock(&p->loaderMutex);
        int i = p->loaderCount++;
        pthread_mutex_unlock(&p->loaderMutex);

        if(i >= p->batch.index){
            break;
        }

        Image img = LoadImage(p->batch.paths[i]);
    
        if(img.data == NULL){
            continue;
        }else{
            ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
        }

        bufferPush(&p->loaded, img);
        pthread_mutex_lock(&p->loaderMutex);
        int i = p->loadedCount++;
        pthread_mutex_unlock(&p->loaderMutex);
    }

    pthread_exit(NULL);
}



void applyEnhancement(Image *img, const char *type){
    if(type == NULL || img->data == NULL) return;

    if(strcmp(type, WARMTH) == 0){
        warmth(img);
    }
    else if(strcmp(type, BRIGHTEN) == 0){
        brighten(img);
    }
    else if(strcmp(type, CONTRAST) == 0){
        contrast(img);
    }
    else if(strcmp(type, SHARPEN) == 0){
        sharpen(img);
    }
    else if(strcmp(type, SATURATE) == 0){
        saturate(img);
    }
}

void* enhancer(void* param){
    Pipeline* p = param;

    while(1){
        pthread_mutex_lock(&p->enhancerMutex);
        int i = p->enhancerCount++;
        pthread_mutex_unlock(&p->enhancerMutex);

        if(i >= p->batch.index){
            break;
        }

        Image img = bufferPop(&p->filtered);

        if(img.data == NULL){
            continue;
        }

        applyEnhancement(&img, p->enhancerName);

        bufferPush(&p->enhanced, img);

        pthread_mutex_lock(&p->enhancerMutex);
        int i = p->enhancedCount++;
        pthread_mutex_unlock(&p->enhancerMutex);
    }

    pthread_exit(NULL);
}

void applyFilter(Image* img, const char* type){
    if(type == NULL || img->data == NULL) return;

    if(strcmp(type , GRAYSCALE) == 0){
        filterGrayscale(img);
    } 
    else if(strcmp(type , FUNKY) == 0){
        filterFunky(img);
    } 
    else if(strcmp(type , INVERT) == 0){
        filterInvert(img);
    }
    else if(strcmp(type , SEPIA) == 0){
        filterSepia(img);
    }
}

void* filter(void* param){
    Pipeline *p = param;

    while(1){
        pthread_mutex_lock(&p->filterMutex);
        int i= p->filterCount++;
        pthread_mutex_unlock(&p->filterMutex);

        if(i >= p->batch.index){
            break;
        }

        Image img = bufferPop(&p->loaded);


        applyFilter(&img, p->filterName);

        bufferPush(&p->filtered , img);

        pthread_mutex_lock(&p->filterMutex);
        int i= p->filteredCount++;
        pthread_mutex_unlock(&p->filterMutex);
    }
    pthread_exit(NULL);
}



void* saver(void* param){
    Pipeline* p = param;

    mkdir("./output", 0777);              

    while(1){
        pthread_mutex_lock(&p->saverMutex);
        int i = p->saverCount++;
        pthread_mutex_unlock(&p->saverMutex);

        if(i >= p->batch.index){
            break;
        }

        Image img = bufferPop(&p->enhanced);
        if(img.data == NULL){
            continue;
        }

        const char* srcPath = p->batch.paths[i];
        const char* filename = strrchr(srcPath, '/');
        const char* justName = filename ? filename + 1 : srcPath;  
        char outPath[512];
        strcpy(outPath, "./output/");   
        strcat(outPath, justName);    

        ExportImage(img, outPath);
        UnloadImage(img);
        pthread_mutex_lock(&p->saverMutex);
        int i = p->savedCount++;
        pthread_mutex_unlock(&p->saverMutex);
    }
    pthread_exit(NULL);
}