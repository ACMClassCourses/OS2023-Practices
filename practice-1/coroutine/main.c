#include "coroutine.h"
#include "utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

cid_t getid_val = -1;

int test_costart(void){
    printf("Hello World!\n");
    return 100;
}

int nested_costart(void){
    cid_t nested = co_start(test_costart);
    if(nested < 0) fail("Nested creation failed", __func__, __LINE__);
    co_wait(nested);
    return 200;
}

int test_yield1(void){
    printf("Coroutine #1 before yield.\n");
    co_yield();
    printf("Coroutine #1 after yield.\n");
    return 0;
}

int test_yield2(void){
    printf("Coroutine #2 before yield.\n");
    co_yield();
    printf("Coroutine #2 after yield.\n");
    return 0;
}

int test_dummy(void){
    return 1;
}

int test_getid(void){
    getid_val = co_getid();
    return getid_val;
}

//test multithread
_Atomic int total_coroutine_count = 0;

int test_multithread_coroutine_inner() {
    total_coroutine_count++;
    return 1;
}

int test_multithread_coroutine() {
    // printf("Running: %d, thread: %ld\n", co_getid(), pthread_self());
    const int CNT = 10;
    cid_t coroutine[CNT];
    for (int i = 0; i < CNT; ++i) {
        coroutine[i] = co_start(test_multithread_coroutine_inner);
        co_yield();
        if (i > 1) {
            co_wait(coroutine[i - 1]);
            assert(co_status(coroutine[i - 1]) == FINISHED);
        }
        co_yield();
        assert(co_status(co_getid()) == RUNNING);
        co_yield();
    }
    co_wait(coroutine[CNT - 1]);
    assert(co_status(coroutine[CNT - 1]) == FINISHED);
    // printf("Coroutine finished: %d\n", co_getid());
    return 1;
}

void* test_multithread_thread(void *ptr) {
    // printf("Thread: %ld\n", pthread_self());
    const int CNT = 20;
    cid_t coroutine[CNT];
    for (int i = 0; i < CNT; ++i) {
        coroutine[i] = co_start(test_multithread_coroutine);
    }
    for (int i = 0; i < CNT; ++i) {
        assert(co_getret(coroutine[i]) == 1);
        assert(co_status(coroutine[i]) == FINISHED);
    }
    // printf("Thread finished: %ld\n", pthread_self());
}

int test_multithread() {
    const int CNT = 50;
    pthread_t threads[CNT];
    total_coroutine_count = 0;
    int ret;
    for (int i = 0; i < CNT; ++i) {
        ret = pthread_create(threads + i, NULL, test_multithread_thread, NULL);
    }
    for (int i = 0; i < CNT; ++i) {
        pthread_join(threads[i], NULL);
    }
    assert(total_coroutine_count == 10000);
    return 0;
}

int test_multithread_timer() {
    // close output when timing
    struct timeval stop, start;
    gettimeofday(&start, NULL);
    test_multithread();
    gettimeofday(&stop, NULL);
    printf("Multithread time: %lf ms\n", (stop.tv_sec - start.tv_sec) * 1000 + (stop.tv_usec - start.tv_usec) / 1000.0);
}

int main(){
    srand(0);
    cid_t coroutine[20];
    // test start routine
    for(int i = 0; i < 10; ++i){
        coroutine[i] = co_start(test_costart);
        if(coroutine[i] != i) fail("Coroutine ID not equal", __func__, __LINE__);
    }
    // test wait: not necessary if 1-N, think why
    co_waitall();
    // test get return value
    for(int i = 0; i < 10; ++i) {
        if(co_getret(coroutine[i]) != 100) fail("Coroutine return value failed", __func__, __LINE__);
    }
    // test nested creation
    coroutine[0] = co_start(nested_costart);
    if(coroutine[0] != 10) fail("Nested coroutine ID not equal", __func__, __LINE__);
    if(co_getret(coroutine[0]) != 200) fail("Nested coroutine return value failed", __func__, __LINE__);
    // test nested and get status
    for(int i = 0; i < 12; ++i) if(co_status(i) != FINISHED) fail("Coroutine failed at status error", __func__, __LINE__);
    // test yield and get status
    coroutine[0] = co_start(test_yield1);
    printf("Main: after co_start\n");
    coroutine[1] = co_start(test_yield2);
    for(int i = 0; i < 2; ++i) while(co_status(coroutine[i]) != FINISHED) co_yield();
    printf("Main: after 2 coroutine yields.\n");
    // test getid
    for(int i = 0; i < 10; ++i) coroutine[i] = co_start(test_dummy);
    co_waitall();
    coroutine[0] = co_start(test_getid);
    co_wait(coroutine[0]);
    if(coroutine[0] != getid_val) fail("Get ID differs from internal getid", __func__, __LINE__);
    if(coroutine[0] != co_getret(getid_val)) fail("Get ID differs from internal return value", __func__, __LINE__);
    printf("Main: test getid finished.\n");
    test_multithread();
    test_multithread_timer();
    printf("Finish running.\n");
    return 0;
}
