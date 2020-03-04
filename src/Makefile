all:	main

main:	main.o	batalhaNaval.o
	gcc	main.o	batalhaNaval.o	-o	main
	
main.o:	main.c 
	gcc	-g	-c	main.c

batalhaNaval.o:	batalhaNaval.c	batalhaNaval.h
	gcc	-g	-c	batalhaNaval.c

clean:
	rm	-f	*.o	main

