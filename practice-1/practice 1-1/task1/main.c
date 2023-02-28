#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXTHREAD 10

void *thread1(void* dummy){
    int i;
    printf("This is thread %d!\n", *((int*) dummy));
    for(i = 0; i < 20; ++i){
        printf("H");
        printf("e");
        printf("l");
        printf("l");
        printf("o");
        printf("W");
        printf("o");
        printf("r");
        printf("l");
        printf("d");
        printf("!");
    }
    return NULL;
}

int main(){
    pthread_t pid[MAXTHREAD];
    int i;
    for(i = 0; i < MAXTHREAD; ++i){
        int* thr = (int*) malloc(sizeof(int)); 
        *thr = i;
        // 1 Loc here: create thread and pass thr as parameter
    }
    for(i = 0; i < MAXTHREAD; ++i)
        // 1 Loc here: join thread
    return 0;
}
