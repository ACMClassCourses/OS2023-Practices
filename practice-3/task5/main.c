#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(){
    
    pid_t pid;
    // OPEN FILES
    int fd;
    fd = open("test.txt" , O_RDWR | O_CREAT | O_TRUNC);
    if (fd == -1)
    {
        /* code */
    }
    //write 'hello fcntl!' to file

    /* code */

    

    // DUPLICATE FD

    /* code */
    
    

    pid = fork();

    if(pid < 0){
        // FAILS
        printf("error in fork");
        return 1;
    }
    
    struct flock fl;

    if(pid > 0){
        // PARENT PROCESS
        //set the lock

        //append 'b'
        
        //unlock
        sleep(3);

        // printf("%s", str); the feedback should be 'hello fcntl!ba'
        
        exit(0);

    } else {
        // CHILD PROCESS
        sleep(2);
        //get the lock
        
        //append 'a'

        exit(0);
    }
    close(fd);
    return 0;
}