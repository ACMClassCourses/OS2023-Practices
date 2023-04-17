all:
	gcc -o gen gen.c
	gcc -o write write.c -O0
	gcc -o read read.c -O0
	./gen data.tmp

run-write:
	./write data.tmp

run-read:
	./read data.tmp

clean:
	rm gen write read data.tmp 
