#define ok(expr) \
    do{ \
        if(!((expr) || fake_mode)){ \
            printf("[%d]Assertion failed: " #expr " at %d\n", tCnt, __LINE__); \
            if(!cont) exit(-1); \
        } else { \
            printf("[%d]Ok: " #expr " at %d\n", tCnt, __LINE__); \
            tCnt++; \
        } \
    } while(0) 


#define dotOk(expr) \
    do{ \
        if(!((expr) || fake_mode)){ \
            printf("X==>FAILED!\n"); \
            printf("[%d]Assertion failed: " #expr " at %d\n", tCnt, __LINE__); \
            if(!cont) exit(-1); \
        } else { \
            printf("."); \
            fflush(stdout); \
            tCnt++; \
        } \
    } while(0) 

#define dotDone() \
    do {    \
        printf("\nTotal: %d Ok\n", tCnt);    \
    } while (0) 

#define finish() \
    do {    \
        printf("\nTest Ends.\n");    \
    } while (0) 