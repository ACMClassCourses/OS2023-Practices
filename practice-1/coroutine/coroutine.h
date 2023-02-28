/* YOUR CODE HERE */
#ifndef COROUTINE_H
#define COROUTINE_H

typedef long long cid_t;
#define MAXN 10
#define UNAUTHORIZED -1
#define FINISHED 2
#define RUNNING 1

int co_start(int (*routine)(void));
int co_getid();
int co_getret(int cid);
int co_yield();
int co_waitall();
int co_wait(int cid);
int co_status(int cid);

#endif