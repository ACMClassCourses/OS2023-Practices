#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

const int BUF_SIZE = 100;

int main(int argc, char *argv[]) {
	char *message;

	message = (char *) mmap(NULL, BUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	if (fork() == 0) {
		sleep(1);
		printf("child got a message :%s\n", message);
		sprintf(message, "%s", "hi, dad, this is son");
	} else {
		sprintf(message, "%s", "hi, this is father");
		sleep(2);
		printf("parent got a message: %s\n", message);
	}

	munmap(message, BUF_SIZE);

	return 0;
}