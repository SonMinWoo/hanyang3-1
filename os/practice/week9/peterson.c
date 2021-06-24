/*
 * Copyright 2021. Heekuck Oh, all rights reserved
 * 이 프로그램은 한양대학교 ERICA 소프트웨어학부 재학생을 위한 교육용으로 제작되었습니다.
 */
#include <stdio.h>
#include <time.h>
#include <pthread.h>

int alive = 1;
int flag[2];
int turn;

/*
 * Peterson의 해법을 이용하여 두 스레드가 임계구역에 배타적으로 들어간다.
 */
void *worker(void *arg)
{
    int i = *(int *)arg;
    int j = (i+1)%2;
    int k;
    
    while (alive) {
        flag[i] = 1;
        turn = j;
        while (flag[j] && turn == j)
            ;
        /*
         * 임계구역 시작: A 또는 B 문자를 한 줄에 40개씩 10줄 출력한다.
         */
        for (k = 0; k < 400; ++k) {
            printf("%c", 'A'+i);
            if ((k+1) % 40 == 0)
                printf("\n");
        }
        /*
         * 임계구역 종료
         */
        flag[i] = 0;
    }
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t tid[2];
    int id[2] = {0,1};
    struct timespec req;
    /*
     * 두 개의 자식 스레드를 생성한다.
     */
    pthread_create(tid, NULL, worker, id);
    pthread_create(tid+1, NULL, worker, id+1);
    /*
     * 스레드가 실행될 동안 0.5 마이크로초 잠잔다.
     */
    req.tv_sec = 0;
    req.tv_nsec = 500000L;
    nanosleep(&req, NULL);
    /*
     * 스레드가 자연스럽게 무한 루프를 빠져나올 수 있게 한다.
     */
    alive = 0;
    /*
     * 자식 스레드가 종료될 때까지 기다린다.
     */
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    /*
     * 메인을 종료한다.
     */
    return 0;
}
