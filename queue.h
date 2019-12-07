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

#endif