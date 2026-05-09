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

void* saturate(Image *img){
    Color *pixels = (Color *)img->data;
    int pixelCount = img->width * img->height;
    float saturationFactor = 1.7f;
    for(int i = 0; i < pixelCount; i++){
        float gray = 0.299f * pixels[i].r + 0.587f * pixels[i].g + 0.114f * pixels[i].b;
        int r = (int)(gray + (pixels[i].r - gray) * saturationFactor);
        int g = (int)(gray + (pixels[i].g - gray) * saturationFactor);
        int b = (int)(gray + (pixels[i].b - gray) * saturationFactor);
        pixels[i].r = (r > 255) ? 255 : (r < 0 ? 0 : (unsigned char)r);
        pixels[i].g = (g > 255) ? 255 : (g < 0 ? 0 : (unsigned char)g);
        pixels[i].b = (b > 255) ? 255 : (b < 0 ? 0 : (unsigned char)b);
    }

}

void* sharpen(Image *img){
    Color *pixels = (Color *)img->data;
    int pixelCount = img->width * img->height;
    Color *src = (Color *)malloc(pixelCount * sizeof(Color));
    memcpy(src, pixels, pixelCount * sizeof(Color));

    int w = img->width;
    int h = img->height;

    for(int y = 1; y < h - 1; y++){
        for(int x = 1; x < w - 1; x++){

            int i = y * w + x;
            int r = (src[i].r * 5) - src[i - 1].r - src[i + 1].r - src[i - w].r - src[i + w].r;
            int g = (src[i].g * 5) - src[i - 1].g - src[i + 1].g - src[i - w].g - src[i + w].g;
            int b = (src[i].b * 5) - src[i - 1].b - src[i + 1].b - src[i - w].b - src[i + w].b;
            pixels[i].r = (r > 255) ? 255 : (r < 0 ? 0 : (unsigned char)r);
            pixels[i].g = (g > 255) ? 255 : (g < 0 ? 0 : (unsigned char)g);
            pixels[i].b = (b > 255) ? 255 : (b < 0 ? 0 : (unsigned char)b);
        }
    }
    free(src);
}

