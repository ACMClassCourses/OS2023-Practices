#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define FILE_SIZE 67108864

char c[FILE_SIZE];

int main(int argc, char *argv[]) {

	for (int i = 0; i < FILE_SIZE; i++)
		c[i] = '#';

	int fd = open(argv[1], O_CREAT | O_RDWR, S_IRWXU);
	if (fd == -1) {
		fprintf(stderr, "fail on open %s\n", argv[1]);
		return -1;
	}

	int write_bytes = write(fd, c, FILE_SIZE);
	printf("successfully write %d bytes to %s\n", write_bytes, argv[1]);

	close(fd);
	return 0;
}