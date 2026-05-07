#include "../include/buffer.h"

void bufferPush(Buffer* buf, Image img){
    sem_wait(&buf->empty);
    pthread_mutex_lock(&buf->lock);

    buf->slots[buf->tail] = img;
    buf->tail = (buf->tail + 1) % buf->capacity;
    buf->count++;

    pthread_mutex_unlock(&buf->lock);
    sem_post(&buf->full);
}

Image bufferPop(Buffer* buf){
    sem_wait(&buf->full);
    pthread_mutex_lock(&buf->lock);

    Image item = buf->slots[buf->head];
    buf->head = (buf->head + 1) % buf->capacity;
    buf->count--;

    pthread_mutex_unlock(&buf->lock);
    sem_post(&buf->empty);

    return item;
}

void bufferInit(Buffer* buf , int capacity){
    buf->slots = malloc(sizeof(Image)*capacity);
    if(!buf->slots){
        fprintf(stderr , "bufferInit: malloc failed");
        exit(1);
    }
    buf->capacity = capacity;
    buf->head = 0;
    buf->tail = 0;
    buf->count = 0;

    pthread_mutex_init(&buf->lock, NULL);
    sem_init(&buf->empty, 0, capacity);
    sem_init(&buf->full,  0, 0);
}


void bufferDestroy(Buffer * buf){
    free(buf->slots);
    buf->slots = NULL;
    pthread_mutex_destroy(&buf->lock);
    sem_destroy(&buf->empty);
    sem_destroy(&buf->full);
}