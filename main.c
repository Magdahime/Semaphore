/*==============================================================================
                        Magdalena Majkowska 
Bufor 9 elementowy FIFO. Dwóch konsumentów i dwóch producentów. Producent A
produkuję literę A, producent B produkuję literę B. Producent A może zapisywać
elementy do bufora jedynie gdy ich liczba elementów w buforze większa niż 5.
Odczyt (usunięcie) jest dozwolone, gdy liczba elementów w buforze jest większa 
niż 3. 
==============================================================================*/


#include <stdio.h>
#include "monitor.h"
#include "queue.h"
#include <unistd.h>
#define MIN_BUFOR 3 //minimalna liczba elementów w buforze dla prod.A

/*     Zdefiniowany czas dla każdego z producentów i konsumentów */
#define PRODUCER_A_MAX_SLEEP 4
#define PRODUCER_B_MAX_SLEEP 5
#define PRODUCER_A_MIN_SLEEP 3
#define PRODUCER_B_MIN_SLEEP 0

#define CONSUMER1_MAX_SLEEP  3
#define CONSUMER2_MAX_SLEEP  3
#define CONSUMER1_MIN_SLEEP  0
#define CONSUMER2_MIN_SLEEP  0
/*
full ----> do pilnowania żeby nikt nie czytał z przepełnionego buforu
empty ---> do pilnowania żeby nikt nie czytał z pustego buforu
mutex ---> do zmieniania zawartości buforu tylko przez jeden wątek
*/
Semaphore full(MAX), empty(0), mutex(1);

void read_queue(struct FIFOqueue* queue){
    printf("\t[ ");
    for(int i=0; i<MAX; i++){
        if(*queue[i]==0) printf("_ ");
        else printf("%c", *queue[i]);
    }
        printf("]\n ");
}


