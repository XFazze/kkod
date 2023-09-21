#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>      
#include<semaphore.h>   
#include<time.h>        

pthread_mutex_t mutexBuffer;
sem_t semItems;

int N;
int timeInterval;
int count;
int bufferSize;
int* buffer= NULL;                   // Buffer works as a stack FILO

void* producer(void* args){     
    while(1){
        int x = rand() % 100;               // Producer creates product, a random number between 1 & 10
        sleep(timeInterval);
        printf("Producer %d of %d. New num=%d \n", count, bufferSize, x );
        if(count<bufferSize){
            pthread_mutex_lock(&mutexBuffer);
            buffer[count] = x;                  // Allocates the product to the buffer
            count++;
            pthread_mutex_unlock(&mutexBuffer);
            sem_post(&semItems);
        }
            
    }
}

void* consumer(void* args){
    while(1){
        int y;
        sem_wait(&semItems);                 // Waits for a product in the buffer 
        pthread_mutex_lock(&mutexBuffer);
        y = buffer[count-1];              // Consumer removes product from the buffer
        count--;
        
        pthread_mutex_unlock(&mutexBuffer);

        printf("Consumer=%ld Consumes %d \n",  pthread_self(),y);
        // sleep(timeInterval);
     }
}

int main(void){
    srand(time(NULL));

    printf("Insert number of consumers: ");
    scanf("%d", &N);
    
    printf("Insert buffersize: ");
    scanf("%d", &bufferSize);
    // int buffer[bufferSize];
    buffer = calloc(bufferSize, sizeof(int));
    
    printf("Insert number of seconds between generated data by the producer: ");
    scanf("%d", &timeInterval);

    pthread_t prod;
    pthread_t cons[N];
    
    pthread_mutex_init(&mutexBuffer, NULL);
    sem_init(&semItems, 0, 0);

    //Create producer
    pthread_create(&prod, NULL, &producer, NULL);
    
    //Create consumers
    for(int i = 0; i < N; i++){
        pthread_create(&cons[i], NULL, &consumer, NULL);
    }

    for(int i = 0; i < N; i++){
        pthread_join(cons[i], NULL);
    }
    pthread_join(prod, NULL);

    pthread_mutex_destroy(&mutexBuffer);
    sem_destroy(&semItems);
    free(buffer);

    return 0;
}