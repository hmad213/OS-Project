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