 #include <time.h>

/*==============================================================================
                        Magdalena Majkowska 
Bufor 9 elementowy FIFO. Dwóch konsumentów i dwóch producentów. Producent A
produkuję literę A, producent B produkuję literę B. Producent A może zapisywać
elementy do bufora jedynie gdy ich liczba elementów w buforze większa niż 5.
Odczyt (usunięcie) jest dozwolone, gdy liczba elementów w buforze jest większa 
niż 3. 
==============================================================================*/

#include "/home/magdalena/Dokumenty/PW_projects/SOI/Lab3/include/queue.h"
#include "/home/magdalena/Dokumenty/PW_projects/SOI/Lab3/include/monitor.h"

#define MIN_BUFFER 3 //minimalna liczba elementów w buforze dla konsumentów
#define MIN_PROD_A 5

/*     Zdefiniowany czas dla każdego z producentów i konsumentów */
#define PRODUCER_A_MAX_SLEEP 1
#define PRODUCER_B_MAX_SLEEP 1

#define CONSUMER1_MAX_SLEEP  5
#define CONSUMER2_MAX_SLEEP  5
/*
full ----> do pilnowania żeby nikt nie dorzucał do przepełnionego buforu
empty ---> do pilnowania żeby nikt nie czytał z pustego buforu
mutex ---> do zmieniania zawartości buforu tylko przez jeden wątek
*/

    Semaphore full(MAX), empty(0), mutex(1), wake(1);
    struct FIFOqueue queue;

void wait(int how_much){
    usleep(1000000*how_much);
}

void* consumer1(void * ptr){
    for(;;){
        wait(CONSUMER1_MAX_SLEEP);
        printf("Konsument 1 próbuje zdjąć...\n");
        empty.p();
        mutex.p();
        if(size(queue)> MIN_BUFFER){
            printf("Konsument 1 zdejmuje %c\n",peek(queue));
            removeData(&queue);
            read_queue(queue);
            full.v();
            printf("Konsument 1 zakończył działanie.\n");
        }
        mutex.v();
    }
}

void* consumer2(void * ptr){
    for(;;){
        wait(CONSUMER2_MAX_SLEEP);
        printf("Konsument 2 próbuje zdjąć...\n");
        empty.p();
        mutex.p();
        if(size(queue)> MIN_BUFFER){
            printf("Konsument 2 zdejmuje %c\n",peek(queue));
            removeData(&queue);
            read_queue(queue);
            full.v();
            printf("Konsument 2 zakończył działanie.\n");
        } 
        mutex.v();

    }
}
void* producerA(void* ptr){
    for(;;){
        wait(PRODUCER_A_MAX_SLEEP);
        printf("Producent A próbuje dodać...\n");
        full.p();
        mutex.p();
        if(size(queue)> MIN_PROD_A){
            printf("Producent A dodaje do kolejki.\n");
            insert(&queue, "A");
            read_queue(queue);
            printf("Aktualny rozmiar kolejki: %d\n", size(queue));
            printf("Producent A zakończył działanie.\n");
            empty.v();
        }else {
        full.v();
        }
        mutex.v();
    }
}
void* producerB(void* ptr){
    for(;;){
        wait(PRODUCER_B_MAX_SLEEP);
        printf("Producent B próbuje dodać ...\n");
        full.p();
        mutex.p();
        printf("Producent B dodaje do kolejki.\n");
        insert(&queue, "B");
        read_queue(queue);
        printf("Aktualny rozmiar kolejki: %d\n", size(queue));
        empty.v();
        mutex.v();
        printf("Producent B zakończył działanie.\n");
    }
}

int main(void){
    //URUCHOMIENIE WĄTKÓW
    pthread_t konsument_1, konsument_2, producent_A, producent_B;

    queue.tail =-1;
    queue.head=0;
    queue.item_count=0;

    pthread_create(&producent_A,NULL, producerA,NULL);
    pthread_create(&producent_B,NULL, producerB,NULL);
    pthread_create(&konsument_1,NULL, consumer1,NULL);
    pthread_create(&konsument_2,NULL, consumer2,NULL);

    pthread_join(producent_A, NULL);
    pthread_join(producent_B, NULL);
    pthread_join(konsument_1, NULL);
    pthread_join(konsument_2, NULL);
    ///KONIEC PROGRAMU
    printf("==============================================================================\n");
    printf("Stan kolejki na koniec działania programu: \n");
    read_queue(queue);
    printf("KONIEC.\n");
    return 0;
}