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

void* applyEnhancement(Image *img, const char *type){
    if(type == NULL || img->data == NULL) return;

    Color *pixels = (Color *)img->data;
    int pixelCount = img->width * img->height;

    //apply different enhancement on each pixel using math formulas
    if(strcmp(type, "Invert") == 0){
        for(int i = 0; i < pixelCount; i++){
            pixels[i].r = 255 - pixels[i].r;
            pixels[i].g = 255 - pixels[i].g;
            pixels[i].b = 255 - pixels[i].b;
            
        }
    } 
    else if(strcmp(type, "Warmth") == 0){
        for(int i = 0; i < pixelCount; i++){
            int r = pixels[i].r + 30;
            int b = pixels[i].b - 20;
            pixels[i].r = (r > 255) ? 255 : (unsigned char)r;
            pixels[i].b = (b < 0) ? 0 : (unsigned char)b;
        }
    }
    else if(strcmp(type, "Brighten") == 0){
        for(int i = 0; i < pixelCount; i++){
            int r = pixels[i].r + 40;
            int g = pixels[i].g + 40;
            int b = pixels[i].b + 40;
            pixels[i].r = (r > 255) ? 255 : (unsigned char)r;
            pixels[i].g = (g > 255) ? 255 : (unsigned char)g;
            pixels[i].b = (b > 255) ? 255 : (unsigned char)b;
        }
    }
    else if(strcmp(type, "Contrast") == 0){
        float factor = 1.5f; 
        for(int i = 0; i < pixelCount; i++){
            int r = (int)((pixels[i].r - 128) * factor + 128);
            int g = (int)((pixels[i].g - 128) * factor + 128);
            int b = (int)((pixels[i].b - 128) * factor + 128);
            pixels[i].r = (r > 255) ? 255 : (r < 0 ? 0 : (unsigned char)r);
            pixels[i].g = (g > 255) ? 255 : (g < 0 ? 0 : (unsigned char)g);
            pixels[i].b = (b > 255) ? 255 : (b < 0 ? 0 : (unsigned char)b);
        }
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