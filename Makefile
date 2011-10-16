test: test.c stdio_.h uCini/uCini.c uCini/uCini.h ini_map.h Makefile
	cp -f stdio_.h uCini
	gcc -o test test.c uCini/uCini.c

ini_map.h: gentest uCini/uCini_gen.pl
	uCini/uCini_gen.pl gentest >$@
