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
        printf("loader: %d\n", i);

        Image img = LoadImage(p->batch.paths[i]);
    
        if(img.data == NULL){
            continue;
        }else{
            ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
        }

        bufferPush(&p->loaded, img);
        printf("pushed\n");
    }

    pthread_exit(NULL);
}



void applyEnhancement(Image *img, const char *type){
    if(type == NULL || img->data == NULL) return;

    if(strcmp(type, "Warmth") == 0){
        warmth(img);
    }
    else if(strcmp(type, "Brighten") == 0){
        brighten(img);
    }
    else if(strcmp(type, "Contrast") == 0){
        contrast(img);
    }
    else if(strcmp(type, "Sharpen") == 0){
        sharpen(img);
    }
    else if(strcmp(type, "Saturate") == 0){
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
        printf("HEllo from enhancer!\n");

        if(img.data == NULL){
            continue;
        }

        applyEnhancement(&img, p->enhancerName);

        printf("Enhanced!\n");

        bufferPush(&p->enhanced, img);
    }

    pthread_exit(NULL);
}

void applyFilter(Image* img, const char* type){
    if(type == NULL || img->data == NULL) return;

    if(strcmp(type , "grayscale") == 0){
        filterGrayscale(img);
    } 
    else if(strcmp(type , "funky") == 0){
        filterFunky(img);
    } 
    else if(strcmp(type , "invert") == 0){
        filterInvert(img);
    }
    else if(strcmp(type , "sepia") == 0){
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

        printf("HEllo from filterer!\n");

        printf("Applying filter: %s\n", p->filterName);
        applyFilter(&img, p->filterName);

        printf("Filtered\n");
        bufferPush(&p->filtered , img);
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
    }
    pthread_exit(NULL);
}