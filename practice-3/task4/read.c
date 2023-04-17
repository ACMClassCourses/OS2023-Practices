#include <stdio.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define FILE_SIZE 67108864

char c[FILE_SIZE];

int PAGE_SIZE;

const int try_step[7] = {128, 256, 512, 1024, 2048, 4096, 8192};

double dur(struct timeval start, struct timeval end) {
	return (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) * 1e-6;
}

double syscall_read_test(int step, char* file_name) {
	struct timeval v_start, v_end, start, end;
	int fd;

	gettimeofday(&v_start, NULL);
	fd = open(file_name, O_CREAT | O_RDWR);
	if (fd == -1) {
		fprintf(stderr, "fail on open %s\n", file_name);
		return -1;
	}
	gettimeofday(&start, NULL);
	for (int i = 0; i < FILE_SIZE; i += step) {
		read(fd, c + i, step);
	}
	gettimeofday(&end, NULL);
	close(fd);
	gettimeofday(&v_end, NULL);

	return dur(start, end);
	// printf("syscall read pure %.3f s whole %.3f s\n", dur(start, end), dur(v_start, v_end));
}

double mmap_read_test(int step, char* file_name) {
	struct timeval v_start, v_end, start, end;
	int fd;
	struct stat sb;
	char *mmaped = NULL;

	gettimeofday(&v_start, NULL);
	fd = open(file_name, O_CREAT | O_RDWR, S_IRWXU);
	if (fd == -1) {
		fprintf(stderr, "fail on open %s\n", file_name);
		return -1;
	}
	if (stat(file_name, &sb) == -1) {
		fprintf(stderr, "fail on stat %s\n", file_name);
		close(fd);
		return -1;
	}
	
	mmaped = (char *)mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (mmaped == (char *)-1) {
		fprintf(stderr, "fail on mmap %s\n", file_name);
		close(fd);
		return -1;
	}
	gettimeofday(&start, NULL);
	for (int i = 0; i < FILE_SIZE; i += step) {
		memcpy(c + i, mmaped + i, step);
	}
	gettimeofday(&end, NULL);
	close(fd);
	gettimeofday(&v_end, NULL);

	return dur(start, end);
	// printf("mmap read pure %.3f s whole %.3f s\n", dur(start, end), dur(v_start, v_end));
}

int main(int argc, char *argv[]) {
	PAGE_SIZE = getpagesize();

	for (int i = 0; i < FILE_SIZE; i++)
		c[i] = '#';

	for (int i = 6; i >= 0; i--) {
		double syscall_read_time = syscall_read_test(try_step[i], argv[1]);
		double mmap_read_time = mmap_read_test(try_step[i], argv[1]);
		printf("step: %d bytes syscall read: %.3f s mmap read: %.3f s\n", try_step[i], syscall_read_time, mmap_read_time);
	}
	return 0;
}
