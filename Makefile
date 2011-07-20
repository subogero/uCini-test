test: test.c stdio_.h uCini/uCini.c uCini/uCini.h Makefile
	cp -f stdio_.h uCini
	gcc -o test test.c uCini/uCini.c
