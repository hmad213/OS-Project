#ifndef RENDERER_H
#define RENDERER_H

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600

#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include "pipeline.h"

extern char error[100];

void drawSelectorStage(char** pathArray, int* count, int maxCount, Font font, int* stage);
void drawButton(Rectangle bounds, const char* text, Color color);
void drawFilterStage(Font f, char**, int*);
void drawEnhancerStage(Font f, char**, int*);
void drawProgressStage(Pipeline* p);
void drawFinishStage(Font font);

#endif