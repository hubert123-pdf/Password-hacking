#include "MD5.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define PRODUCER_THREADS 3
#define CONSUMER_THREAD 1



void* Producer0(void* arg)
{
    
}
void* Producer1(void* arg)
{
    
}
void* Producer2(void* arg)
{
    
}
void* Consumer(void* arg)
{
    
}
int main(int argc, char* argv[])
{
    char password[32];
    pthread_t thread[PRODUCER_THREADS+CONSUMER_THREAD];
    
    pthread_create(&thread[0],NULL,Producer0,(void*)password) ; 
    pthread_create(&thread[1],NULL,Producer1,(void*)password) ; 
    pthread_create(&thread[2],NULL,Producer2,(void*)password) ; 
    pthread_create(&thread[3],NULL,Consumer,(void*)password) ; 

    for(int i=0;i<PRODUCER_THREADS+CONSUMER_THREAD;i++)
    {
        pthread_join(thread[i],NULL);
        printf("Thread %d is done. \n",i);
    }
    pthread_exit(NULL);

}
