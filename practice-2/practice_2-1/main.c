#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "buddy.h"
#include "utils.h"
int fake_mode = 0;
int cont = 0;

#define MAXRANK (16)
#define TESTSIZE (128)
#define MAXRANK0PAGE (TESTSIZE * 1024 / 4)
int tCnt = 0;

int pow2f(int n){
    if(n <= 0) return 1;
    return 2 * pow2f(n - 1);
}

int main(){
    void *p, *q;
    int ret, pgIdx, freeCnt, currentRank;

    printf("Unit test suite: \nPhase 1: \n");

    p = malloc(TESTSIZE * sizeof(char) * 1024 * 1024);
    ret = init_page(p, MAXRANK0PAGE);
    ok(ret == OK);

    printf("Phase 2: alloc pages\n");
    tCnt = 0;
    q = p;
    for(pgIdx = 0; pgIdx < MAXRANK0PAGE; pgIdx++, q = q + 1024 * 4){
        void *r = alloc_pages(1);
        dotOk(r == q);
    }
    dotDone();
    void *r = alloc_pages(1);
    ok(PTR_ERR(r) == -ENOSPC);

    printf("Phase 3: query_page_counts test #1(empty)\n");
    tCnt = 0;
    for(pgIdx = 1; pgIdx <= MAXRANK; ++pgIdx){
        dotOk(query_page_counts(pgIdx) == 0);
    }
    dotDone();

    printf("Phase 4: return pages\n");
    tCnt = 0;
    q = p;
    ok(PTR_ERR(return_pages(NULL)) == -EINVAL);
    ok(PTR_ERR(return_pages(p + TESTSIZE * 1024 * 1024 + 16)) == -EINVAL);
    for(pgIdx = 0; pgIdx < MAXRANK0PAGE; pgIdx++, q = q + 1024 * 4){
        ret = return_pages(q);
        dotOk(ret == OK);
    }
    dotDone();

    printf("Phase 5: query_page_counts test #2(full)\n");
    tCnt = 0;
    for(pgIdx = 1; pgIdx <= MAXRANK - 1; ++pgIdx){
        dotOk(query_page_counts(pgIdx) == 0);
    }
    dotOk(query_page_counts(MAXRANK) != 0);
    dotDone();

    printf("Phase 6: query ranks(big)\n");
    tCnt = 0;
    q = p;
    ret = query_ranks(q);
    ok(ret == MAXRANK);

    printf("Phase 7: query ranks(small) + alloc page\n");
    tCnt = 0;
    q = p;
    for(pgIdx = 0; pgIdx < MAXRANK0PAGE; pgIdx++, q = q + 1024 * 4){
        void *r = alloc_pages(1);
        ret = query_ranks(r);
        dotOk(ret == 1);
    }
    dotDone();

    printf("Phase 8A: mixed 1\n");
    tCnt = 0;
    for(pgIdx = 0; pgIdx < MAXRANK0PAGE; pgIdx++, q = q + 1024 * 4){
        void *r = alloc_pages(1);
    }
    dotOk(query_page_counts(MAXRANK) == 0);
    q = p;
    currentRank = 1;
    while(currentRank <= MAXRANK){
        int returnPages = pow2f(currentRank - 2);
        int pageReturnIdx = 0, rankIdx = 1;
        for(; pageReturnIdx < returnPages; ++pageReturnIdx, q = q + 1024 * 4)
            ret = return_pages(q);
        while(rankIdx < currentRank) {
            dotOk(query_page_counts(rankIdx) == 0);
            rankIdx++;
        }
        dotOk(query_page_counts(currentRank) == 1);
        currentRank += 1;
    }
    dotDone();

    printf("Phase 8B: mixed 2\n");
    tCnt = 0;
    q = p;
    for(pgIdx = 0; pgIdx < MAXRANK0PAGE; pgIdx++, q = q + 1024 * 4){
        void *r = alloc_pages(1);
    }
    q = p;
    
    for(pgIdx = 0; pgIdx < MAXRANK0PAGE; pgIdx += 2, q = q + 1024 * 4 * 2){
        ret = return_pages(q);
        freeCnt += 1;
        dotOk(query_page_counts(1) == freeCnt);
    }
    q = p + 1024 * 4;
    for(pgIdx = 0; pgIdx < MAXRANK0PAGE; pgIdx += 2, q = q + 1024 * 4){
        ret = return_pages(q);
        freeCnt -= 1;
        dotOk(query_page_counts(1) == freeCnt);
    }
    dotOk(query_page_counts(MAXRANK) != 0);
    dotDone();

    finish();


    return 0;
}