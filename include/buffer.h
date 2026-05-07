#ifndef BUFFER_H
#define BUFFER_H

#include "raylib.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>

typedef struct {
    Image* slots;
    int capacity;
    int head, tail, count;
    pthread_mutex_t lock;
    sem_t empty;
    sem_t full;
} Buffer;

void bufferPush(Buffer* buf, Image img);
Image bufferPop(Buffer* buf);
void bufferInit(Buffer* buf, int capacity);
void bufferDestroy(Buffer* buf);

#endif