/*
 * Copyright 2021. Heekuck Oh, all rights reserved
 * 이 프로그램은 한양대학교 ERICA 소프트웨어학부 재학생을 위한 교육용으로 제작되었습니다.
 */

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* 
 * 뮤텍스를 이용하여 Producer-Consumer 문제를 해결하세요. 
 * 아이템이 소비되었을 때 하나의 Producer가 아이템을 공급해야되고
 * 아이템이 공급되었을 때 하나의 Consumer가 아이템을 소비해야합니다.
 */
#define N 5
sem_t empty;
sem_t full;
int arg[5] = {1,2,3,4,5};
int in = 0;
int out = 0;
int buffer[N];
pthread_mutex_t mutex;

void *producer(void *pno)
{   
    int item;
    for(int i = 0; i < N; i++) {
        item = rand(); // Produce an random item
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer %d: Insert Item %d at %d\n", *((int *)pno),buffer[in],in);
        in = (in+1)%N;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *cno)
{   
    for(int i = 0; i < N; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        printf("Consumer %d: Remove Item %d from %d\n",*((int *)cno),item, out);
        out = (out+1)%N;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main()
{   
    pthread_t pro[N],con[N];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,N);
    sem_init(&full,0,0);

    for(int i = 0; i < N; i++) {
        pthread_create(&pro[i], NULL, producer, arg+i);
    }
    usleep(1);
    for(int i = 0; i < N; i++) {
        pthread_create(&con[i], NULL, consumer, arg+i);
    }

    for(int i = 0; i < N; i++) {
        pthread_join(pro[i], NULL);
    }
    for(int i = 0; i < N; i++) {
        pthread_join(con[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
    
}
