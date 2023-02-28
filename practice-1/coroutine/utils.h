#include <stdio.h>
#include <unistd.h>

inline void fail(const char* message, const char* function, int line){
    printf("[x] Test failed at %s: %d: %s\n", function, line, message);
    exit(-1);
}