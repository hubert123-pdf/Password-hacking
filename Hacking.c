
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <openssl/md5.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define PRODUCER_THREADS 3
#define CONSUMER_THREAD 1

FILE *passwords,*dictionary;
char emails[1000][64];
char passwords_to_hack[1000][32];
char *example_password;
int k=0;
pthread_mutex_t consumer_mutex,mutex1,mutex2;
pthread_cond_t cv1;

void MD5_digest(char argv[],unsigned char tab[])
{
    char password[32];
    for (int i = 0; i < 32; i++){
        password[i]=argv[i];
    }

    MD5_CTX context;
    unsigned char digest[16];
    unsigned int len = strlen (password);

    MD5_Init(&context);
    MD5_Update (&context, password, len);
    MD5_Final(digest, &context);

    for (int i = 0; i < 16; i++){
        tab[i]=digest[i];
    }
}
void* Producer0(void* arg)
{
    while(!feof(dictionary))
    {
        unsigned char tab[16];
        char password_string[32];
        char buff1[33];
        char buff2[33];
        example_password=malloc(sizeof(char)*32);
        fscanf(dictionary,"%s",example_password);
        MD5_digest(example_password,tab);
        for (int i = 0; i < 16; i++){
            sprintf(&password_string[i*2], "%02x", (unsigned int)tab[i]);
        }
        for (int i = 0; i < 32; i++)
        {
            buff1[i]=passwords_to_hack[k][i];
            buff2[i]=password_string[i];
        }
        if(strcmp(buff1,buff2)==0){
            printf("email:%s password:%s\n",emails[k],example_password);
            rewind(dictionary);
            pthread_mutex_lock(&mutex1);
            k++;
            pthread_mutex_unlock(&mutex1);
        }
        free(example_password);
    }

}
void* Producer1(void* arg)
{
    while(!feof(dictionary))
    {
        unsigned char tab[16];
        char password_string[32];
        char buff1[33];
        char buff2[33];
        example_password=malloc(sizeof(char)*32);
        fscanf(dictionary,"%s",example_password);
        example_password[0]=toupper(example_password[0]);
        MD5_digest(example_password,tab);
        for (int i = 0; i < 16; i++){
            sprintf(&password_string[i*2], "%02x", (unsigned int)tab[i]);
        }
        for (int i = 0; i < 32; i++)
        {
            buff1[i]=passwords_to_hack[k][i];
            buff2[i]=password_string[i];
        }
        if(strcmp(buff1,buff2)==0){
            printf("email:%s password:%s\n",emails[k],example_password);
            rewind(dictionary);
            pthread_mutex_lock(&mutex1);
            k++;
            pthread_mutex_unlock(&mutex1);
        }
        free(example_password);
    }

}
void* Producer2(void* arg)
{
    //oczekiwanie na sygnał od konsumenta
    //pthread_cond_wait(&cv1, &mutex1);
    while(!feof(dictionary))
    {
        unsigned char tab[16];
        char password_string[32];
        char buff1[33];
        char buff2[33];
        example_password=malloc(sizeof(char)*32);
        fscanf(dictionary,"%s",example_password);
        for (int i = 0; i < 32; i++){
            example_password[i]=toupper(example_password[i]);
        }
        MD5_digest(example_password,tab);
        for (int i = 0; i < 16; i++){
            sprintf(&password_string[i*2], "%02x", (unsigned int)tab[i]);
        }
        for (int i = 0; i < 32; i++)
        {
            buff1[i]=passwords_to_hack[k][i];
            buff2[i]=password_string[i];
        }
        if(strcmp(buff1,buff2)==0){
            printf("email:%s password:%s\n",emails[k],example_password);
            rewind(dictionary);
            pthread_mutex_lock(&mutex1);
            k++;
            pthread_mutex_unlock(&mutex1);
        }
        free(example_password);
    }
}
void* Consumer(void* arg)
{
    char *new_passwords;
   // scanf("%s",new_passwords);
}
int main(int argc, char* argv[])
{
    long i=0;
    if((passwords=fopen(argv[1],"r"))==NULL){
                printf("ERROR1\n");
                return 0;
    }
    if((dictionary=fopen(argv[2],"r"))==NULL)
    { 
        printf("ERROR2\n");
        return 0;
    }
    while(!feof(passwords))
    {
        fscanf(passwords,"%s",emails[i]);
        fscanf(passwords,"%s",passwords_to_hack[i]);
        i++;
    }
    pthread_t thread[PRODUCER_THREADS+CONSUMER_THREAD];
    pthread_mutex_init(&mutex1, NULL);
    pthread_cond_init (&cv1, NULL);
    pthread_create(&thread[3],NULL,Consumer,(void*)i); 
    pthread_create(&thread[0],NULL,Producer0,(void*)i); 
    pthread_create(&thread[1],NULL,Producer1,(void*)i); 
    pthread_create(&thread[2],NULL,Producer2,(void*)i); 
    for(int i=0;i<PRODUCER_THREADS+CONSUMER_THREAD;i++)
    {
        pthread_join(thread[i],NULL);
        printf("Thread %d is done. \n",i);
    }
    pthread_exit(NULL);
}