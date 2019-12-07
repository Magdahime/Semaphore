#include "queue.h"
#include <string.h>
bool isEmpty(struct FIFOqueue queue) {
    return (queue.item_count==0);
}

bool isFull(struct FIFOqueue queue) {
    return (queue.item_count==MAX);
}

void insert(struct FIFOqueue* queue, char* data) {
    if(!isFull(*queue)&& strlen(data)<2){

        if(queue->tail==MAX-1){
            queue->tail = -1;
        }
    queue->queue[++queue->tail] = *data;
    queue->item_count++;

    }
}

int removeData(struct FIFOqueue* queue) {
    char data = queue->queue[queue->head++];
    if(queue->head ==MAX){
        queue->head =0;
    }
    queue->item_count--;
    return data;
}

void read_queue(struct FIFOqueue queue){
    printf("\t[ ");
    for(int i=0; i<MAX; i++){
        if(queue.queue[i]<65 ||queue.queue[i]> 90) printf("_ ");
        else printf("%c ", queue.queue[i]);
    }
        printf("]\n ");
}
int main(){
    struct FIFOqueue queue;
    queue.tail =-1;
    insert(&queue,"A");
    read_queue(queue);
    insert(&queue,"B");
    read_queue(queue);
    insert(&queue,"C");
    read_queue(queue);
    insert(&queue,"D");
    read_queue(queue);
    insert(&queue,"E");
    read_queue(queue);
}
