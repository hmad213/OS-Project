#include "../include/filters.h"

void filterBrighten(Image * img){
    Color * pixels = (Color*)img->data;
    int pixelcount = img->width * img->height;
    for(int i=0 ; i < pixelcount ; i++ ){
        int r = pixels[i].r + 40;
        int g = pixels[i].g + 40;
        int b = pixels[i].b + 40;

        pixels[i].r = (r > 255) ? 255 : (unsigned char)r;
        pixels[i].g = (g > 255) ? 255 : (unsigned char)g;
        pixels[i].b = (b > 255) ? 255 : (unsigned char)b;
        
    }
}



void filterGrayscale(Image * img){
    Color * pixels = (Color*)img->data;
    int pixelcount = img->width * img->height;
    for(int i=0 ; i < pixelcount ; i++ ){
        unsigned char gray = (unsigned char)(0.299f * pixels[i].r +
                                             0.587f * pixels[i].g +
                                             0.114f * pixels[i].b);
        pixels[i].r = gray;
        pixels[i].g = gray;
        pixels[i].b = gray;
    }
}



void filterInvert(Image* img) {
    Color* pixels = (Color*)img->data;
    int pixelCount = img->width * img->height;

    for (int i = 0; i < pixelCount; i++) {
        pixels[i].r = 255 - pixels[i].r;
        pixels[i].g = 255 - pixels[i].g;
        pixels[i].b = 255 - pixels[i].b;
    }
}

void filterContrast(Image* img, float factor) {
    Color* pixels = (Color*)img->data;
    int pixelCount = img->width * img->height;

    for (int i = 0; i < pixelCount; i++) {
        int r = (int)((pixels[i].r - 128) * factor + 128);
        int g = (int)((pixels[i].g - 128) * factor + 128);
        int b = (int)((pixels[i].b - 128) * factor + 128);

        pixels[i].r = (r < 0) ? 0 : (r > 255) ? 255 : (unsigned char)r;
        pixels[i].g = (g < 0) ? 0 : (g > 255) ? 255 : (unsigned char)g;
        pixels[i].b = (b < 0) ? 0 : (b > 255) ? 255 : (unsigned char)b;
    }
}


void filterSepia(Image* img) {
    Color* pixels = (Color*)img->data;
    int pixelCount = img->width * img->height;

    for (int i = 0; i < pixelCount; i++) {
        int r = (int)(pixels[i].r * 0.393f + pixels[i].g * 0.769f + pixels[i].b * 0.189f);
        int g = (int)(pixels[i].r * 0.349f + pixels[i].g * 0.686f + pixels[i].b * 0.168f);
        int b = (int)(pixels[i].r * 0.272f + pixels[i].g * 0.534f + pixels[i].b * 0.131f);
        pixels[i].r = (r > 255) ? 255 : (unsigned char)r;
        pixels[i].g = (g > 255) ? 255 : (unsigned char)g;
        pixels[i].b = (b > 255) ? 255 : (unsigned char)b;
    }
}



void filterFunky(Image* img) {
    Color* pixels = (Color*)img->data;
    int pixelCount = img->width * img->height;

    float rWeight = 0.5f + ((rand() % 100) / 100.0f);
    float gWeight = 0.5f + ((rand() % 100) / 100.0f);
    float bWeight = 0.5f + ((rand() % 100) / 100.0f);

    for (int i = 0; i < pixelCount; i++) {
        int r = (int)(pixels[i].r * rWeight);
        int g = (int)(pixels[i].g * gWeight);
        int b = (int)(pixels[i].b * bWeight);

        pixels[i].r = (r > 255) ? 255 : (unsigned char)r;
        pixels[i].g = (g > 255) ? 255 : (unsigned char)g;
        pixels[i].b = (b > 255) ? 255 : (unsigned char)b;
    }
}