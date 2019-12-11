#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 9

struct FIFOqueue{
    int queue[MAX];
    int head;
    int tail;
    int item_count;
};

char peek(struct FIFOqueue queue);
int size(struct FIFOqueue queue);
bool isEmpty(struct FIFOqueue queue);
bool isFull(struct FIFOqueue queue);
void insert(struct FIFOqueue* queue, char* data);
int removeData(struct FIFOqueue* queue);
void read_queue(struct FIFOqueue queue);

#endif