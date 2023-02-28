// ? Loc here: header modification to adapt pthread_barrier
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
// 2 Locs here: declare mutex and barrier
void *thread1(void* dummy){
    int i;
    // 1 Loc: mutex operation
    // 1 Loc: barrier operation
    printf("This is thread 1!\n");
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
    // 1 Loc: mutex operation
    return NULL;
}

void *thread2(void* dummy){
    int i;
    // 1 Loc: mutex operation
    // 1 Loc: barrier operation
    printf("This is thread 2!\n");
    for(i = 0; i < 20; ++i){
        printf("A");
        printf("p");
        printf("p");
        printf("l");
        printf("e");
        printf("?");
    }
    // 1 Loc: mutex operation
    return NULL;
}
int main(){
    pthread_t pid[2];
    int i;
    // 1 Loc: barrier initialization
    // 3 Locs here: create 2 thread using thread1 and thread2 as function.
    // mutex initialization
    // 1 Loc: barrier operation
    for(i = 0; i < 2; ++i){
        // 1 Loc code here: join thread
    }
    return 0;
}
