#include "../include/enhancers.h"

//apply different enhancement on each pixel using math formulas

void* warmth(Image *img){
    Color *pixels = (Color *)img->data;
    int pixelCount = img->width * img->height;
    for(int i = 0; i < pixelCount; i++){
            int r = pixels[i].r + 30;
            int b = pixels[i].b - 20;
            pixels[i].r = (r > 255) ? 255 : (unsigned char)r;
            pixels[i].b = (b < 0) ? 0 : (unsigned char)b;
        }
}

void* brighten(Image *img){
    Color *pixels = (Color *)img->data;
    int pixelCount = img->width * img->height;
    for(int i = 0; i < pixelCount; i++){
        int r = pixels[i].r + 40;
        int g = pixels[i].g + 40;
        int b = pixels[i].b + 40;
        pixels[i].r = (r > 255) ? 255 : (unsigned char)r;
        pixels[i].g = (g > 255) ? 255 : (unsigned char)g;
        pixels[i].b = (b > 255) ? 255 : (unsigned char)b;
    }
}

void* contrast(Image *img){
    Color *pixels = (Color *)img->data;
    int pixelCount = img->width * img->height;
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

// will add definition later

void* sharpen(Image *img){
    Color *pixels = (Color *)img->data;
    int pixelCount = img->width * img->height;

}

void* saturate(Image *img){
    Color *pixels = (Color *)img->data;
    int pixelCount = img->width * img->height;

}

