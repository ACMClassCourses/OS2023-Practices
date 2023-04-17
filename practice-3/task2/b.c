#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[]) {

	int fd = -1;
	struct stat sb;
	char *mmaped = NULL;

	fd = open(argv[1], O_RDWR);
	if (fd == -1) {
		fprintf(stderr, "fail on open %s\n", argv[1]);
		return -1;
	}

	if (stat(argv[1], &sb) == -1) {
		fprintf(stderr, "fail on stat %s\n", argv[1]);
		close(fd);
		return -1;
	}

	mmaped = (char *)mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (mmaped == (char *)-1) {
		fprintf(stderr, "fail on mmap %s\n", argv[1]);
		close(fd);
		return -1;
	}

	close(fd);

	mmaped[42] = '!';
	mmaped[43] = '\0';

	munmap(mmaped, sb.st_size);

	return 0;
}