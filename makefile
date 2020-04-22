a.out: base.o extras.o main.o
	gcc -o a.out base.o extras.o main.o

base.o: base.c base.h record.h
	gcc -c base.c

extras.o: extras.c extras.h record.h
	gcc -c extras.c

main.o: main.c base.h extras.h record.h
	gcc -c main.c

clean: rm a.out base.o extras.o main.o
